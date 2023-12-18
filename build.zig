const std = @import("std");
const Build = std.build;

pub fn build(b: *Build) void {
    //const target = b.standardTargetOptions(.{});
    //const optimize = b.standardOptimizeOption(.{});

    const exe = b.addExecutable(.{
        .name = "pang",
        //.optimize = optimize,
        //.target = target,
        .optimize = b.standardOptimizeOption(.{}),
        .target = b.standardTargetOptions(.{}),
    });
    exe.addCSourceFiles(.{
        .files = &.{
            "src/ball.c",
            "src/bonus.c",
            "src/collisions.c",
            "src/events.c",
            "src/gfx.c",
            "src/ladder.c",
            "src/levels.c",
            "src/main.c",
            "src/objects.c",
            "src/platform.c",
            "src/player.c",
            "src/shoot.c",
            "src/sound.c",
            "src/structures.c",
            "src/ui.c",
        },
    });

    exe.addIncludePath(.{ .path = "src" });

    exe.linkSystemLibrary("c");
    exe.linkSystemLibrary("sdl2");
    exe.linkSystemLibrary("SDL2_mixer");
    exe.linkSystemLibrary("SDL2_image");
    b.installArtifact(exe);

    const play = b.step("play", "Play the game");
    const run = b.addRunArtifact(exe);
    run.step.dependOn(b.getInstallStep());
    play.dependOn(&run.step);
}
