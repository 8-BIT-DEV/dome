typedef enum {
  AUDIO_TYPE_UNKNOWN,
  AUDIO_TYPE_WAV,
  AUDIO_TYPE_OGG
} AUDIO_TYPE;



struct CHANNEL_t {
  CHANNEL_STATE state;
  CHANNEL_ID id;
  volatile bool enabled;
  bool stopRequested;
  CHANNEL_mix mix;
  CHANNEL_callback update;
  CHANNEL_callback finish;

  void* userdata;
};

typedef struct {
  SDL_AudioSpec spec;
  AUDIO_TYPE audioType;
  // Length is the number of LR samples
  uint32_t length;
  // Audio is stored as a stream of interleaved normalised values from [-1, 1)
  float* buffer;
} AUDIO_DATA;

struct AUDIO_CHANNEL_PROPS {
  // Control variables
  bool loop;
  // Playback variables
  float volume;
  float pan;
  // Position is the sample value to play next
  volatile size_t position;
  bool resetPosition;
};

typedef struct {
  struct AUDIO_CHANNEL_PROPS current;
  struct AUDIO_CHANNEL_PROPS new;
  char* soundId;
  float actualVolume;
  float actualPan;
  bool fade;

  AUDIO_DATA* audio;
  WrenHandle* audioHandle;
} AUDIO_CHANNEL;

internal void AUDIO_CHANNEL_mix(CHANNEL* base, float* stream, size_t totalSamples);
internal void AUDIO_CHANNEL_update(WrenVM* vm, CHANNEL* base);
internal void AUDIO_CHANNEL_finish(WrenVM* vm, CHANNEL* base);
internal void CHANNEL_requestStop(CHANNEL* channel);
