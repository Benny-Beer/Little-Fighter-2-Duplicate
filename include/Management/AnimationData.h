#pragma once

struct AnimationInfo {
    int x;
    int y;
    int width;
    int height;
    int frameCount;
    float frameTime;
    bool loop;
};


inline const AnimationInfo WALKING = { 320, 0, 80, 80, 4, 0.2f, true };
inline const AnimationInfo WALKING_WITH_ROCK = { 320, 160, 80, 80, 4, 0.2f, true };
inline const AnimationInfo STANDING = { 0, 0, 80, 80, 3, 0.3f, true };
inline const AnimationInfo STANDING_WITH_ROCK = { 320, 160, 80, 80, 0, 0.2f, false };
inline const AnimationInfo JUMPING = { 0, 520, 80, 80, 4, 0.1f, false };

inline const AnimationInfo JUMPING_WITH_ROCK = { 0, 520, 80, 80, 4, 0.1f, false };
inline const AnimationInfo ATTACKING_WITH_ROCK = { 560, 160, 80, 80, 2, 0.1f, false };
inline const AnimationInfo ATTACKING = { 0, 80, 80, 80, 4, 0.1f, true };
inline const AnimationInfo IDLE = { 195, 0, 40, 40, 0, 0.2f, false};
inline const AnimationInfo ROCK = {295, 0, 58, 58, 0, 0.2f, false };
inline const AnimationInfo BOX = { 299, 0, 58, 58, 0, 0.2f, false };
inline const AnimationInfo ROCK_FLYING = { 2, 0, 59, 58, 4, 0.2f, true};

inline const AnimationInfo ATTACKING_WITH_KNIFE = { 0, 0, 58, 58, 1, 0.2f, false };
inline const AnimationInfo WALKING_WITH_KNIFE = { 0, 0, 58, 58, 2, 0.2f, true };
inline const AnimationInfo HELD = { 146, 98, 42, 46, 0, 0.7f, true };
inline const AnimationInfo BOX_EXPLOIDING = { 58, 0, 58, 58, 2, 0.2f, false };
inline const AnimationInfo BLOCKING = { 0, 0, 58, 58, 1, 0.2f, false };
inline const AnimationInfo KNOCKEDDOWN = { 240, 240, 80, 80, 2, 0.2f, false };





