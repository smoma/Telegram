//
// libtgvoip is free and unencumbered public domain software.
// For more information, see http://unlicense.org or the UNLICENSE file
// you should have received with this source code distribution.
//

#ifndef LIBTGVOIP_VIDEOTOOLBOXENCODERSOURCE
#define LIBTGVOIP_VIDEOTOOLBOXENCODERSOURCE

#include "../../video/VideoSource.h"
#include <CoreMedia/CoreMedia.h>
#include <VideoToolbox/VideoToolbox.h>
#include <vector>

#ifdef __OBJC__
@class TGVVideoSource;
#else
typedef struct objc_object TGVVideoSource;
#endif

namespace tgvoip{
	namespace video{
		class VideoToolboxEncoderSource : public VideoSource{
		public:
			VideoToolboxEncoderSource(TGVVideoSource* parent);
			virtual ~VideoToolboxEncoderSource();
			virtual void Start() override;
			virtual void Stop() override;
			virtual void Reset(uint32_t codec, int maxResolution) override;
			virtual void RequestKeyFrame() override;
			virtual void SetBitrate(uint32_t bitrate) override;
			void EncodeFrame(CMSampleBufferRef frame);
			void SetStreamPaused(bool paused);
			static std::vector<uint32_t> GetAvailableEncoders();
			static bool SupportsFullHD();
		private:
			void EncoderCallback(OSStatus status, CMSampleBufferRef buffer, VTEncodeInfoFlags flags);
			void SetEncoderBitrateAndLimit(uint32_t bitrate);
			bool needUpdateStreamParams=true;
			uint32_t codec=0;
			VTCompressionSessionRef session=NULL;
			bool keyframeRequested=false;
			uint32_t bitrateChangeRequested=0;
			uint32_t lastBitrate=512*1024;
			unsigned int lastFrameRate=0;
			TGVVideoSource* objcObject;
		};
	}
}

#endif /* LIBTGVOIP_VIDEOTOOLBOXENCODERSOURCE */
