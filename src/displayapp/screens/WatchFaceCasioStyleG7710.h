#pragma once

#include <displayapp/screens/BatteryIcon.h>
#include <lvgl/src/lv_core/lv_obj.h>
#include <chrono>
#include <cstdint>
#include <memory>
#include <displayapp/Controllers.h>
#include "displayapp/screens/Screen.h"
#include "components/datetime/DateTimeController.h"
#include "components/ble/BleController.h"
#include "utility/DirtyValue.h"
#include "displayapp/apps/Apps.h"
#include "displayapp/InfiniTimeTheme.h"
#include "displayapp/Colors.h"

namespace Pinetime {
  namespace Controllers {
    class Settings;
    class Battery;
    class Ble;
    class NotificationManager;
    class HeartRateController;
    class MotionController;
  }

  namespace Applications {
    namespace Screens {

      class WatchFaceCasioStyleG7710 : public Screen {
      public:
        WatchFaceCasioStyleG7710(Controllers::DateTime& dateTimeController,
                                 const Controllers::Battery& batteryController,
                                 const Controllers::Ble& bleController,
                                 Controllers::NotificationManager& notificatioManager,
                                 Controllers::Settings& settingsController,
                                 Controllers::HeartRateController& heartRateController,
                                 Controllers::MotionController& motionController,
                                 Controllers::FS& filesystem);
        ~WatchFaceCasioStyleG7710() override;

        void Refresh() override;

        static bool IsAvailable(Pinetime::Controllers::FS& filesystem);

      private:
        Utility::DirtyValue<uint8_t> batteryPercentRemaining {};
        Utility::DirtyValue<bool> powerPresent {};
        Utility::DirtyValue<bool> bleState {};
        Utility::DirtyValue<bool> bleRadioEnabled {};
        Utility::DirtyValue<std::chrono::time_point<std::chrono::system_clock, std::chrono::minutes>> currentDateTime {};
        Utility::DirtyValue<uint32_t> stepCount {};
        Utility::DirtyValue<uint8_t> heartbeat {};
        Utility::DirtyValue<bool> heartbeatRunning {};
        Utility::DirtyValue<bool> notificationState {};
        Utility::DirtyValue<std::chrono::time_point<std::chrono::system_clock, std::chrono::days>> currentDate;

        lv_point_t line_icons_points[3] {{0, 5}, {117, 5}, {122, 0}};
        lv_point_t line_day_of_week_number_points[4] {{0, 0}, {100, 0}, {95, 95}, {0, 95}};
        lv_point_t line_day_of_year_points[3] {{0, 5}, {130, 5}, {135, 0}};
        lv_point_t line_date_points[3] {{0, 5}, {135, 5}, {140, 0}};
        lv_point_t line_time_points[3] {{0, 0}, {230, 0}, {235, 5}};

        // lv_color_t color_text = lv_color_hex(0xFFFFFF);
        // lv_color_t color_red = lv_color_hex(0xFB4934);
        // lv_color_t color_orange = lv_color_hex(0xFE8019);
        // lv_color_t color_yellow = lv_color_hex(0xFABD2F);
        // lv_color_t color_green = lv_color_hex(0xB8BB26);
        // lv_color_t color_blue = lv_color_hex(0x83A598);
        // lv_color_t color_magenta = lv_color_hex(0xD3869B);
        lv_color_t color_text = Colors::white;
        lv_color_t color_red = Colors::red;
        lv_color_t color_orange = Colors::orange;
        lv_color_t color_yellow = Colors::yellow;
        lv_color_t color_green = Colors::green;
        lv_color_t color_blue = Colors::blue;
        lv_color_t color_magenta = Colors::magenta;

        lv_style_t style_line;
        lv_style_t style_border;

        lv_obj_t* label_time;
        lv_obj_t* line_time;
        lv_obj_t* label_time_ampm;
        lv_obj_t* label_date;
        lv_obj_t* line_date;
        lv_obj_t* label_day_of_week;
        lv_obj_t* label_week_number;
        lv_obj_t* line_day_of_week_number;
        lv_obj_t* label_day_of_year;
        lv_obj_t* line_day_of_year;
        lv_obj_t* backgroundLabel;
        lv_obj_t* bleIcon;
        lv_obj_t* batteryPlug;
        lv_obj_t* label_battery_value;
        lv_obj_t* heartbeatIcon;
        lv_obj_t* heartbeatValue;
        lv_obj_t* stepIcon;
        lv_obj_t* stepValue;
        lv_obj_t* notificationIcon;
        lv_obj_t* line_icons;

        BatteryIcon batteryIcon;

        Controllers::DateTime& dateTimeController;
        const Controllers::Battery& batteryController;
        const Controllers::Ble& bleController;
        Controllers::NotificationManager& notificatioManager;
        Controllers::Settings& settingsController;
        Controllers::HeartRateController& heartRateController;
        Controllers::MotionController& motionController;

        lv_task_t* taskRefresh;
        lv_font_t* font_dot40 = nullptr;
        lv_font_t* font_segment40 = nullptr;
        lv_font_t* font_segment115 = nullptr;
      };
    }

    template <>
    struct WatchFaceTraits<WatchFace::CasioStyleG7710> {
      static constexpr WatchFace watchFace = WatchFace::CasioStyleG7710;
      static constexpr const char* name = "Casio G7710";

      static Screens::Screen* Create(AppControllers& controllers) {
        return new Screens::WatchFaceCasioStyleG7710(controllers.dateTimeController,
                                                     controllers.batteryController,
                                                     controllers.bleController,
                                                     controllers.notificationManager,
                                                     controllers.settingsController,
                                                     controllers.heartRateController,
                                                     controllers.motionController,
                                                     controllers.filesystem);
      };

      static bool IsAvailable(Pinetime::Controllers::FS& filesystem) {
        return Screens::WatchFaceCasioStyleG7710::IsAvailable(filesystem);
      }
    };
  }
}
