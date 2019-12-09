Module.pubCppLib = null;
Module.initialize = function () { return undefined; };

Module.onRuntimeInitialized = function () {
    Module.pubCppLib = new Module.CppLibManager();
}

// Module.postRun = function () {

// }

Module.initWithCanvas = function (canvas) {
    options = {
        majorVersion: 1,
        minorVersion: 0,
        antialias: false,
        stencil: true,
        enableExtensionsByDefault: true
    };
    // use webgl 1.0 for safari
    const ctx = canvas.getContext("webgl", options);
    const handle = GL.registerContext(ctx, options);
    GL.makeContextCurrent(handle);
    Module.pubCppLib.initializeLib();
}

Module.trigerTests = function () {
    if (Module.pubCppLib) {
        Module.pubCppLib.trigerLib(5);
    }
}

Module.runRenderLoop = function () {
    function render(now) {
        if (Module.pubCppLib) {
            Module.pubCppLib.renderFrame();
        }
        requestAnimationFrame(render);
    }
    requestAnimationFrame(render);
}
