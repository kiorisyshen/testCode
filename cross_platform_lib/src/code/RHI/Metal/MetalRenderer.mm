
#import "MetalRenderer.h"

#if !__has_feature(objc_arc)
#error "ARC is off"
#endif

@implementation MetalRenderer {
    id<MTLDevice> _device;

    // The render pipeline generated from the vertex and fragment shaders in the .metal shader file.
    id<MTLRenderPipelineState> _pipelineState;

    // The command queue used to pass commands to the device.
    id<MTLCommandQueue> _commandQueue;

    // The current size of the view, used as an input to the vertex shader.
    float _viewportSize_x;
    float _viewportSize_y;
}

- (nonnull instancetype)initWithMetalKitView:(nonnull MTKView *)mtkView {
    self = [super init];
    if (self) {
        _device = mtkView.device;
        // Create the command queue
        _commandQueue = [_device newCommandQueue];
        
        NSError *error = NULL;
        
        NSString *libraryFile    = [[[NSBundle bundleForClass:self] URLForResource:@"Main" withExtension:@".metallib"] absoluteString];
        NSLog(@"Library path: %@", libraryFile);
        id<MTLLibrary> myLibrary = [_device newLibraryWithFile:libraryFile error:&error];
        if (!myLibrary) {
            NSLog(@"Failed to in create metal library, error %@", error);
            return nil;
        }
        
        id<MTLFunction> vertexFunction   = [myLibrary newFunctionWithName:@"vertexShader"];
        id<MTLFunction> fragmentFunction = [myLibrary newFunctionWithName:@"fragmentShader"];
        
        // Configure a pipeline descriptor that is used to create a pipeline state.
        MTLRenderPipelineDescriptor *pipelineStateDescriptor    = [[MTLRenderPipelineDescriptor alloc] init];
        pipelineStateDescriptor.label                           = @"Simple Pipeline";
        pipelineStateDescriptor.vertexFunction                  = vertexFunction;
        pipelineStateDescriptor.fragmentFunction                = fragmentFunction;
        pipelineStateDescriptor.colorAttachments[0].pixelFormat = mtkView.colorPixelFormat;
        
        _pipelineState = [_device newRenderPipelineStateWithDescriptor:pipelineStateDescriptor
                                                                 error:&error];
        if (!_pipelineState) {
            // Pipeline State creation could fail if the pipeline descriptor isn't set up properly.
            //  If the Metal API validation is enabled, you can find out more information about what
            //  went wrong.  (Metal API validation is enabled by default when a debug build is run
            //  from Xcode.)
            NSLog(@"Failed to created pipeline state, error %@", error);
            return nil;
        }
    }

    return self;
}

- (bool)InitializeShaders {
    bool succ = true;

    return succ;
}

/// Called whenever view changes orientation or is resized
- (void)mtkView:(nonnull MTKView *)view drawableSizeWillChange:(CGSize)size {
    // Save the size of the drawable to pass to the vertex shader.
    _viewportSize_x = size.width;
    _viewportSize_y = size.height;
}

/// Called whenever the view needs to render a frame.
- (void)drawInMTKView:(nonnull MTKView *)view {
    static const float triangleVertices[] =
    {
        // 2D positions,    RGBA colors
        0.5, -0.5, 1, 0, 0, 1,
        -0.5, -0.5, 0, 1, 0, 1,
        0, 0.5, 0, 0, 1, 1,
    };

    // Create a new command buffer for each render pass to the current drawable.
    id<MTLCommandBuffer> commandBuffer = [_commandQueue commandBuffer];
    commandBuffer.label                = @"MyCommand";

    // Obtain a renderPassDescriptor generated from the view's drawable textures.
    MTLRenderPassDescriptor *renderPassDescriptor = view.currentRenderPassDescriptor;

    if (renderPassDescriptor != nil) {
        // Create a render command encoder.
        id<MTLRenderCommandEncoder> renderEncoder =
            [commandBuffer renderCommandEncoderWithDescriptor:renderPassDescriptor];
        renderEncoder.label = @"MyRenderEncoder";

        // Set the region of the drawable to draw into.
        [renderEncoder setViewport:(MTLViewport){0.0, 0.0, _viewportSize_x, _viewportSize_y, 0.0, 1.0}];

        [renderEncoder setRenderPipelineState:_pipelineState];

        // Pass in the parameter data.
        [renderEncoder setVertexBytes:triangleVertices
                               length:sizeof(triangleVertices)
                              atIndex:0];

        // Draw the triangle.
        [renderEncoder drawPrimitives:MTLPrimitiveTypeTriangle
                          vertexStart:0
                          vertexCount:3];

        [renderEncoder endEncoding];

        // Schedule a present once the framebuffer is complete using the current drawable.
        [commandBuffer presentDrawable:view.currentDrawable];
    }

    // Finalize rendering here & push the command buffer to the GPU.
    [commandBuffer commit];
}

@end
