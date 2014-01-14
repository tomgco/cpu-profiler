# strong-cpu-profiler

Provides bindings for the v8 profiler in node.js

- Version 2.0.0 - Compatible with nodejs v0.11 and upwards.
- Version 1.0.0 - Compatible with nodejs v0.10.

Master is upto date with node v0.11 and is not compatible with v0.10.
For a 0.10v compatible checkout the [release/1.0.0](https://github.com/tomgco/cpu-profiler/tree/release/1.0.0)
branch.

## Installation

    npm install strong-cpu-profiler

We now include node v0.10 binaries for a number of platforms.  During the
install, node-gyp will attempt to build the module for your platform.  If it
fails (see builderror.log), the module will still be installed, but will
attempt to load up an appropriate pre-built binary for your platform if there
is one available.

## Usage

    var profiler = require('strong-cpu-profiler');

## API

    profiler.startProfiling([name])                   // start cpu profiling
    var cpuProfile = profiler.stopProfiling([name])   // stop cpu profiling

Or with capturing samples when profiling

    profiler.startProfiling([name], true)                   // start cpu profiling
    var cpuProfile = profiler.stopProfiling([name])   // stop cpu profiling

# Thanks

[Danny Coates](https://github.com/dannycoates) for starting the project
and maintaining it for several years.

[Strongloop](https://github.com/strongloop) for rewriting to work with nodejs
v0.11
