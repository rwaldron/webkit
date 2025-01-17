/*
 * Copyright (C) 2009 Apple Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. AND ITS CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL APPLE INC. OR ITS CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

#import <wtf/Platform.h>

#if PLATFORM(MAC) && ENABLE(VIDEO)

#import <AppKit/NSScreen.h>
#import <AppKit/NSWindowController.h>
#import <wtf/RefPtr.h>

namespace PAL {
class SleepDisabler;
}

namespace WebCore {
class HTMLVideoElement;
}

@protocol WebVideoFullscreenControllerDelegate;
@class WebVideoFullscreenHUDWindowController;
@class WebWindowFadeAnimation;
@class CALayer;

@interface WebVideoFullscreenController : NSWindowController {
@private
    RefPtr<WebCore::HTMLVideoElement> _videoElement; // (retain)
    id <WebVideoFullscreenControllerDelegate> _delegate; // (assign)

    NSWindow *_backgroundFullscreenWindow; // (retain)
    WebVideoFullscreenHUDWindowController *_hudController; // (retain)

    WebWindowFadeAnimation *_fadeAnimation; // (retain)

    BOOL _isEndingFullscreen;
    BOOL _forceDisableAnimation;

    std::unique_ptr<PAL::SleepDisabler> _displaySleepDisabler;
}

- (id <WebVideoFullscreenControllerDelegate>)delegate;
- (void)setDelegate:(id <WebVideoFullscreenControllerDelegate>)delegate;

- (void)setupVideoOverlay:(CALayer*)layer;
- (void)setVideoElement:(WebCore::HTMLVideoElement*)videoElement;
- (WebCore::HTMLVideoElement*)videoElement;

- (void)enterFullscreen:(NSScreen *)screen;
- (void)exitFullscreen;

@end

#endif
