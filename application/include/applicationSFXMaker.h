#ifndef APPLICATION_SFX_MAKER_H__DDK
#define APPLICATION_SFX_MAKER_H__DDK

namespace application { struct AppConfiguration; }
namespace audio { struct Configuration; }

namespace application
{
    class SFXMaker
    {
        public:
            SFXMaker();

            int execute(AppConfiguration const & app_configuration, audio::Configuration const & audio_configuration);

        private:
    };
}

#endif /* APPLICATION_SFX_MAKER_H__DDK */

