LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := libfluidsynth

LOCAL_C_INCLUDES := \
    $(LOCAL_PATH)/include \
    $(LOCAL_PATH)/sdlorg_fork \
    $(LOCAL_PATH)/sdlorg_fork/gcem \
    $(LOCAL_PATH)/sdlorg_fork/android \
    $(LOCAL_PATH)/sdlorg_fork/android/include \
    $(LOCAL_PATH)/src \
    $(LOCAL_PATH)/src/bindings \
    $(LOCAL_PATH)/src/drivers \
    $(LOCAL_PATH)/src/midi \
    $(LOCAL_PATH)/src/rvoice \
    $(LOCAL_PATH)/src/sfloader \
    $(LOCAL_PATH)/src/synth \
    $(LOCAL_PATH)/src/utils

APP_STL := c++_shared

LOCAL_CPP_FEATURES := exceptions rtti
LOCAL_CPPFLAGS := -std=c++17

LOCAL_EXPORT_C_INCLUDES += \
    $(LOCAL_PATH)/include \
    $(LOCAL_PATH)/sdlorg_fork/android/include

LOCAL_SRC_FILES := \
    src/sfloader/fluid_dls.cpp \
    src/utils/fluid_sys_cpp11.cpp \
    src/utils/fluid_file.cpp \
    src/gentables/fluid_ct2hz.cpp \
    src/gentables/fluid_cb2amp.cpp \
    src/gentables/fluid_concave.cpp \
    src/gentables/fluid_convex.cpp \
    src/gentables/fluid_pan.cpp \
    src/gentables/fluid_interp_coeff.cpp \
    src/gentables/fluid_interp_coeff_linear.cpp \
    src/gentables/fluid_interp_coeff_sinc7.cpp \
    src/utils/fluid_conv.c \
    src/utils/fluid_hash.c \
    src/utils/fluid_list.c \
    src/utils/fluid_ringbuffer.c \
    src/utils/fluid_settings.c \
    src/utils/fluid_sys.c \
    src/sfloader/fluid_defsfont.c \
    src/sfloader/fluid_sfont.c \
    src/sfloader/fluid_sffile.c \
    src/sfloader/fluid_samplecache.c \
    src/rvoice/fluid_adsr_env.c \
    src/rvoice/fluid_chorus.c \
    src/rvoice/fluid_iir_filter_impl.cpp \
    src/rvoice/fluid_iir_filter.c \
    src/rvoice/fluid_lfo.c \
    src/rvoice/fluid_rvoice.c \
    src/rvoice/fluid_rvoice_dsp.cpp \
    src/rvoice/fluid_rvoice_event.c \
    src/rvoice/fluid_rvoice_mixer.c \
    src/rvoice/fluid_rev.c \
    src/synth/fluid_chan.c \
    src/synth/fluid_event.c \
    src/synth/fluid_gen.c \
    src/synth/fluid_mod.c \
    src/synth/fluid_synth.c \
    src/synth/fluid_synth_monopoly.c \
    src/synth/fluid_tuning.c \
    src/synth/fluid_voice.c \
    src/midi/fluid_midi.c \
    src/midi/fluid_midi_router.c \
    src/midi/fluid_seqbind.c \
    src/midi/fluid_seqbind_notes.cpp \
    src/midi/fluid_seq.c \
    src/midi/fluid_seq_queue.cpp \
    src/drivers/fluid_adriver.c \
    src/drivers/fluid_mdriver.c \
    src/bindings/fluid_cmd.c \
    src/bindings/fluid_filerenderer.c \
    src/bindings/fluid_ladspa.c

LOCAL_LDLIBS := -llog

LOCAL_LDFLAGS := -Wl,--no-undefined

include $(BUILD_SHARED_LIBRARY)
