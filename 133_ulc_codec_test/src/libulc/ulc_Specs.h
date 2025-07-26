/**************************************/
#pragma once
/**************************************/

/*!
  File header magic value.
!*/
#define ULC_FILE_MAGIC ('U' | 'L'<<8 | 'C'<<16 | '2'<<24)

/*!
  This controls the maximum block size allowed for
  decoding. A larger size uses more memory, but allows
  higher coding gain (up to a limit, anyway; BlockSize=4096
  tends to start degrading from pre/post-echo artifacts).
  Note that on GBA, this is also limited by the amount of
  IWRAM available, as the IMDCT transform buffers are placed
  there instead of EWRAM due to extremely poor waitstates.
!*/
#define ULC_MIN_BLOCK_SIZE_LOG2 6
#define ULC_MIN_BLOCK_SIZE (1 << ULC_MIN_BLOCK_SIZE_LOG2)
#define ULC_MAX_BLOCK_SIZE_LOG2 8
#define ULC_MAX_BLOCK_SIZE (1 << ULC_MAX_BLOCK_SIZE_LOG2)

/*!
  This controls support for stereo decoding.
  Support for stereo audio requires double the memory
  usage for the lapping and playback buffers.
!*/
#define ULC_STEREO_SUPPORT 0

/*!
  This chooses whether to use a LUT for the trig terms
  or a quadrature oscillator. The oscillator is slightly
  faster than the LUT method and uses ~8kB less ROM, but
  is slightly less accurate.
!*/
#define ULC_USE_QUADRATURE_OSC 1

/*!
  This controls the bitdepth of the audio, excluding the
  sign bit (eg. 16bit coefficients would set this to 15).
  This should be set as high as possible, regardless of
  the output audio quality, as IMDCT requires a lot of
  recursive computation and the error propagates between
  each step. The final 8-point DCT stages are also not
  particularly accurate, but as long as this precision
  is kept high, the rounding error should be kept in the
  bits that will be discarded for output.
  I'm honestly not sure what the theoretical maximum is
  here. Each step of the DCT algorithm has an infinity
  norm of 2.0, but that assumes 'any' signal, which is
  not actually the case here, as we have normalized the
  signal in the encoding stages. Setting this value to
  28 doesn't appear to cause internal overflow, but I
  can't 100% guarantee that this is the case.
  This value must NOT be larger than 28. In theory, it's
  possible to set this to 29, but this requires special
  handling in ulc_DecodeBlock() (the shift factor can
  become 0, which requires clearing the LSR flag). If set
  to anything larger, MDCT coefficients will overflow.
  NOTE: This refers to the internal precision, not the
  final audio output; this is always 8bit for GBA.
!*/
#define ULC_COEF_PRECISION 20

/*!
  This allows ulc_StartPlayer() and ulc_StopPlayer() to
  automatically prepare the sound hardware (and DMA) for
  audio playback. Disabling this option will simply decode
  audio data to the output buffers.
!*/
#define ULC_USER_HWSETUP 0

/*!
  This will only decode audio to a single buffer, instead
  of the standard double buffering. This is useful if the
  output is not intended to be played back directly.
  This option requires ULC_USER_HWSETUP.
!*/
#define ULC_SINGLE_BUFFER 1




// fixed 2025/07/26 by akkera102

// #if (ULC_SINGLE_BUFFER && !ULC_USER_HWSETUP)
// # error "ULC_SINGLE_BUFFER requires ULC_USER_HWSETUP."
// #endif




/**************************************/
//! EOF
/**************************************/
