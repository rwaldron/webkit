/*
 * Copyright (C) 2017-2018 Apple Inc. All rights reserved.
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
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "config.h"
#include "KeyframeEffect.h"

namespace WebCore {
using namespace JSC;

ExceptionOr<Ref<KeyframeEffect>> KeyframeEffect::create(ExecState& state, Element* target, Strong<JSObject>&& keyframes, std::optional<Variant<double, KeyframeEffectOptions>>&& options)
{
    auto keyframeEffect = adoptRef(*new KeyframeEffect(AnimationEffectTiming::create(), target));

    auto setPropertiesResult = keyframeEffect->timing()->setProperties(WTFMove(options));
    if (setPropertiesResult.hasException())
        return setPropertiesResult.releaseException();

    auto setKeyframesResult = keyframeEffect->setKeyframes(state, WTFMove(keyframes));
    if (setKeyframesResult.hasException())
        return setKeyframesResult.releaseException();

    return WTFMove(keyframeEffect);
}

ExceptionOr<Ref<KeyframeEffect>> KeyframeEffect::create(JSC::ExecState&, Ref<KeyframeEffectReadOnly>&& source)
{
    auto keyframeEffect = adoptRef(*new KeyframeEffect(AnimationEffectTiming::create(), nullptr));
    keyframeEffect->copyPropertiesFromSource(WTFMove(source));
    return WTFMove(keyframeEffect);
}

KeyframeEffect::KeyframeEffect(Ref<AnimationEffectTimingReadOnly>&& timing, Element* target)
    : KeyframeEffectReadOnly(KeyframeEffectClass, WTFMove(timing), target)
{
}

ExceptionOr<void> KeyframeEffect::setKeyframes(ExecState& state, Strong<JSObject>&& keyframesInput)
{
    return processKeyframes(state, WTFMove(keyframesInput));
}

} // namespace WebCore
