//------------------------------------------------------------------------------
//  UI.cc
//------------------------------------------------------------------------------
#include "UI.h"
#include "yakc_ui/Util.h"
#include "MemoryWindow.h"
#include "MemoryMapWindow.h"
#include "DebugWindow.h"
#include "DisasmWindow.h"
#include "PIOWindow.h"
#include "CTCWindow.h"
#include "ModuleWindow.h"
#include "KeyboardWindow.h"
#include "LoadWindow.h"
#include "CommandWindow.h"
#include "AudioWindow.h"
#include "KC85IOWindow.h"
#include "InfoWindow.h"
#include "Core/Time/Clock.h"
#include "Input/Input.h"
#include "Core/String/StringBuilder.h"
#include "yakc/roms/roms.h"

using namespace Oryol;

namespace YAKC {

ImVec4 UI::DefaultTextColor;
ImVec4 UI::EnabledColor;
ImVec4 UI::DisabledColor;
ImVec4 UI::OkColor;
ImVec4 UI::WarnColor;
ImVec4 UI::EnabledBreakpointColor;
ImVec4 UI::DisabledBreakpointColor;
ImVec4 UI::InvalidOpCodeColor;
ImU32 UI::CanvasTextColor;
ImU32 UI::CanvasLineColor;

//------------------------------------------------------------------------------
void
UI::Setup(yakc& emu, Audio* audio_) {

    this->audio = audio_;
    IMUI::Setup();

    ImGuiStyle style = ImGui::GetStyle();
    style.WindowRounding = 0.0f;
    style.Alpha = 1.0f;
    style.WindowFillAlphaDefault = 1.0f;
    style.WindowTitleAlign = ImGuiAlign_Center;
    style.TouchExtraPadding = ImVec2(5.0f, 5.0f);
    style.AntiAliasedLines = this->imguiAntiAliasedLines;
    style.AntiAliasedShapes = false;
    this->darkTheme = style;

    // bright style from here: https://github.com/ocornut/imgui/pull/511
    style.Colors[ImGuiCol_Text]                  = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
    style.Colors[ImGuiCol_TextDisabled]          = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
    style.Colors[ImGuiCol_WindowBg]              = ImVec4(0.94f, 0.94f, 0.94f, 1.00f);
    style.Colors[ImGuiCol_ChildWindowBg]         = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    style.Colors[ImGuiCol_Border]                = ImVec4(0.00f, 0.00f, 0.00f, 0.39f);
    style.Colors[ImGuiCol_BorderShadow]          = ImVec4(1.00f, 1.00f, 1.00f, 0.10f);
    style.Colors[ImGuiCol_FrameBg]               = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    style.Colors[ImGuiCol_FrameBgHovered]        = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
    style.Colors[ImGuiCol_FrameBgActive]         = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
    style.Colors[ImGuiCol_TitleBg]               = ImVec4(0.96f, 0.96f, 0.96f, 1.00f);
    style.Colors[ImGuiCol_TitleBgCollapsed]      = ImVec4(1.00f, 1.00f, 1.00f, 0.51f);
    style.Colors[ImGuiCol_TitleBgActive]         = ImVec4(0.82f, 0.82f, 0.82f, 1.00f);
    style.Colors[ImGuiCol_MenuBarBg]             = ImVec4(0.86f, 0.86f, 0.86f, 1.00f);
    style.Colors[ImGuiCol_ScrollbarBg]           = ImVec4(0.98f, 0.98f, 0.98f, 0.53f);
    style.Colors[ImGuiCol_ScrollbarGrab]         = ImVec4(0.69f, 0.69f, 0.69f, 0.80f);
    style.Colors[ImGuiCol_ScrollbarGrabHovered]  = ImVec4(0.49f, 0.49f, 0.49f, 0.80f);
    style.Colors[ImGuiCol_ScrollbarGrabActive]   = ImVec4(0.49f, 0.49f, 0.49f, 1.00f);
    style.Colors[ImGuiCol_ComboBg]               = ImVec4(0.86f, 0.86f, 0.86f, 0.99f);
    style.Colors[ImGuiCol_CheckMark]             = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    style.Colors[ImGuiCol_SliderGrab]            = ImVec4(0.26f, 0.59f, 0.98f, 0.78f);
    style.Colors[ImGuiCol_SliderGrabActive]      = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    style.Colors[ImGuiCol_Button]                = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
    style.Colors[ImGuiCol_ButtonHovered]         = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    style.Colors[ImGuiCol_ButtonActive]          = ImVec4(0.06f, 0.53f, 0.98f, 1.00f);
    style.Colors[ImGuiCol_Header]                = ImVec4(0.26f, 0.59f, 0.98f, 0.31f);
    style.Colors[ImGuiCol_HeaderHovered]         = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
    style.Colors[ImGuiCol_HeaderActive]          = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    style.Colors[ImGuiCol_Column]                = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
    style.Colors[ImGuiCol_ColumnHovered]         = ImVec4(0.26f, 0.59f, 0.98f, 0.78f);
    style.Colors[ImGuiCol_ColumnActive]          = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    style.Colors[ImGuiCol_ResizeGrip]            = ImVec4(1.00f, 1.00f, 1.00f, 0.00f);
    style.Colors[ImGuiCol_ResizeGripHovered]     = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
    style.Colors[ImGuiCol_ResizeGripActive]      = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
    style.Colors[ImGuiCol_CloseButton]           = ImVec4(0.59f, 0.59f, 0.59f, 0.50f);
    style.Colors[ImGuiCol_CloseButtonHovered]    = ImVec4(0.98f, 0.39f, 0.36f, 1.00f);
    style.Colors[ImGuiCol_CloseButtonActive]     = ImVec4(0.98f, 0.39f, 0.36f, 1.00f);
    style.Colors[ImGuiCol_PlotLines]             = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
    style.Colors[ImGuiCol_PlotLinesHovered]      = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
    style.Colors[ImGuiCol_PlotHistogram]         = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
    style.Colors[ImGuiCol_PlotHistogramHovered]  = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
    style.Colors[ImGuiCol_TextSelectedBg]        = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
    style.Colors[ImGuiCol_TooltipBg]             = ImVec4(1.00f, 1.00f, 1.00f, 0.94f);
    style.Colors[ImGuiCol_ModalWindowDarkening]  = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);
    this->lightTheme = style;

    this->EnableLightTheme();

    this->fileLoader.Setup(emu);
    this->curTime = Clock::Now();
}

//------------------------------------------------------------------------------
void
UI::Discard() {
    this->fileLoader.Discard();
    this->windows.Clear();
    IMUI::Discard();
}

//------------------------------------------------------------------------------
void
UI::Toggle() {
    this->uiEnabled = !this->uiEnabled;
}

//------------------------------------------------------------------------------
void
UI::OpenWindow(yakc& emu, const Ptr<WindowBase>& win) {
    win->Setup(emu);
    this->windows.Add(win);
}

//------------------------------------------------------------------------------
void
UI::EnableDarkTheme() {
    this->darkThemeEnabled = true;
    this->lightThemeEnabled = false;
    ImGui::GetStyle() = this->darkTheme;
    DefaultTextColor = this->darkTheme.Colors[ImGuiCol_Text];
    EnabledColor = OkColor = ImVec4(0.0f, 1.0f, 0.0f, 1.0f);
    DisabledColor = WarnColor = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
    EnabledBreakpointColor = ImVec4(1.0f, 0.5f, 0.25f, 1.0f);
    DisabledBreakpointColor = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
    InvalidOpCodeColor = ImVec4(1.0f, 0.0f, 1.0f, 1.0f);
    CanvasTextColor = 0xFFFFFFFF;
    CanvasLineColor = 0xFFFFFFFF;
}

//------------------------------------------------------------------------------
void
UI::EnableLightTheme() {
    this->lightThemeEnabled = true;
    this->darkThemeEnabled = false;
    ImGui::GetStyle() = this->lightTheme;
    DefaultTextColor = this->lightTheme.Colors[ImGuiCol_Text];
    EnabledColor = OkColor = ImVec4(0.0f, 0.0f, 1.0f, 1.0f);
    DisabledColor = WarnColor = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
    EnabledBreakpointColor = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
    DisabledBreakpointColor = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
    InvalidOpCodeColor = ImVec4(1.0f, 0.0f, 1.0f, 1.0f);
    CanvasTextColor = 0xFF000000;
    CanvasLineColor = 0xFF000000;
}

//------------------------------------------------------------------------------
void
UI::OnFrame(yakc& emu) {
    o_trace_scoped(yakc_ui);

    StringBuilder strBuilder;
    IMUI::NewFrame(Clock::LapTime(this->curTime));
    // render a single button to enable UI
    ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x - 40, 16));
    if (ImGui::Begin("Menu", nullptr, ImVec2(0,0), 0.0f, ImGuiWindowFlags_NoTitleBar|ImGuiWindowFlags_NoResize))
    {
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.0f, 15.0f));
        if (ImGui::Button("UI ")) {
            this->uiEnabled = !this->uiEnabled;
        }
        if (ImGui::Button("KBD")) {
            if (this->keyboardWindow) {
                this->keyboardWindow = nullptr;
            }
            else {
                this->keyboardWindow = KeyboardWindow::Create();
                this->keyboardWindow->Setup(emu);
            }
        }
        #if ORYOL_EMSCRIPTEN
        if (ImGui::Button("FS ")) {
            if (is_soft_fullscreen_active()) {
                leave_soft_fullscreen();
            }
            else {
                enter_soft_fullscreen();
            }
        }
        #endif
        ImGui::PopStyleVar();
        ImGui::PopStyleColor();
    }
    ImGui::End();
    if (this->uiEnabled) {
        if (ImGui::BeginMainMenuBar()) {
            const char* model;
            switch (emu.model) {
                case device::kc85_2:    model = "KC85/2"; break;
                case device::kc85_3:    model = "KC85/3"; break;
                case device::kc85_4:    model = "KC85/4"; break;
                case device::z1013_01:  model = "Z1013.01"; break;
                case device::z1013_16:  model = "Z1013.16"; break;
                case device::z1013_64:  model = "Z1013.64"; break;
                case device::z9001:     model = "Z9001"; break;
                case device::kc87:      model = "KC87"; break;
                default: model="??"; break;
            }
            if (ImGui::BeginMenu(model)) {
                if (ImGui::MenuItem("System Info...")) {
                    this->OpenWindow(emu, InfoWindow::Create());
                }
                if (ImGui::MenuItem("Load File...")) {
                    auto loadWindow = LoadWindow::Create();
                    loadWindow->SetFileLoader(&this->fileLoader);
                    this->OpenWindow(emu, loadWindow);
                }
                if (ImGui::MenuItem("Power Cycle")) {
                    emu.poweroff();
                    emu.poweron(emu.model, emu.os);
                }
                if (ImGui::MenuItem("Reset")) {
                    emu.reset();
                }
                if (ImGui::BeginMenu("Boot to KC85/2")) {
                    if (emu.kc85.roms.has(kc85_roms::hc900)) {
                        if (ImGui::MenuItem("HC900-CAOS")) {
                            emu.poweroff();
                            emu.poweron(device::kc85_2, os_rom::caos_hc900);
                        }
                    }
                    if (emu.kc85.roms.has(kc85_roms::caos22)) {
                        if (ImGui::MenuItem("HC-CAOS 2.2")) {
                            emu.poweroff();
                            emu.poweron(device::kc85_2, os_rom::caos_2_2);
                        }
                    }
                    ImGui::EndMenu();
                }
                if (ImGui::BeginMenu("Boot to KC85/3")) {
                    if (ImGui::MenuItem("HC-CAOS 3.1")) {
                        emu.poweroff();
                        emu.poweron(device::kc85_3, os_rom::caos_3_1);
                    }
                    if (emu.kc85.roms.has(kc85_roms::caos34)) {
                        if (ImGui::MenuItem("HC-CAOS 3.4i")) {
                            emu.poweroff();
                            emu.poweron(device::kc85_3, os_rom::caos_3_4);
                        }
                    }
                    ImGui::EndMenu();
                }
                if (ImGui::BeginMenu("Boot to KC85/4")) {
                    if (emu.kc85.roms.has(kc85_roms::caos41c) && emu.kc85.roms.has(kc85_roms::caos41e)) {
                        if (ImGui::MenuItem("KC-CAOS 4.1")) {
                            emu.poweroff();
                            emu.poweron(device::kc85_4, os_rom::caos_4_1);
                        }
                    }
                    if (emu.kc85.roms.has(kc85_roms::caos42c) && emu.kc85.roms.has(kc85_roms::caos42e)) {
                        if (ImGui::MenuItem("KC-CAOS 4.2")) {
                            emu.poweroff();
                            emu.poweron(device::kc85_4, os_rom::caos_4_2);
                        }
                    }
                    ImGui::EndMenu();
                }
                if (ImGui::BeginMenu("Boot to Z1013")) {
                    if (ImGui::MenuItem("Z1013.01 (1 MHz, 16KB RAM)")) {
                        emu.poweroff();
                        emu.poweron(device::z1013_01, os_rom::none);
                    }
                    if (ImGui::MenuItem("Z1013.16 (2 MHz, 16KB RAM)")) {
                        emu.poweroff();
                        emu.poweron(device::z1013_16, os_rom::none);
                    }
                    if (ImGui::MenuItem("Z1013.64 (2 MHz, 64KB RAM)")) {
                        emu.poweroff();
                        emu.poweron(device::z1013_64, os_rom::none);
                    }
                    ImGui::EndMenu();
                }
                if (ImGui::MenuItem("Boot to Z9001 (32KB)")) {
                    emu.poweroff();
                    emu.poweron(device::z9001, os_rom::z9001_os_1_2);
                }
                if (ImGui::MenuItem("Boot to KC87  (48KB)")) {
                    emu.poweroff();
                    emu.poweron(device::kc87, os_rom::kc87_os_2);
                }
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Software")) {
                for (const auto& item : this->fileLoader.Items) {
                    if (int(item.Compat) & int(emu.model)) {
                        if (ImGui::MenuItem(item.Name.AsCStr())) {
                            this->fileLoader.LoadAndStart(emu, item);
                        }
                    }
                }
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Hardware")) {
                if (emu.is_device(device::any_kc85)) {
                    if (ImGui::MenuItem("Expansion Slots")) {
                        this->OpenWindow(emu, ModuleWindow::Create());
                    }
                    if (ImGui::MenuItem("Memory Map")) {
                        this->OpenWindow(emu, MemoryMapWindow::Create());
                    }
                    if (ImGui::MenuItem("KC85 IO Ports")) {
                        this->OpenWindow(emu, KC85IOWindow::Create());
                    }
                }
                if (emu.is_device(device::any_z9001)) {
                    // the Z9001 has 2 PIOs
                    if (ImGui::MenuItem("Z80 PIO 1")) {
                        this->OpenWindow(emu, PIOWindow::Create("PIO 1", &emu.board.pio));
                    }
                    if (ImGui::MenuItem("Z80 PIO 2")) {
                        this->OpenWindow(emu, PIOWindow::Create("PIO 2", &emu.board.pio2));
                    }
                }
                else {
                    // all others have 1 PIO
                    if (ImGui::MenuItem("Z80 PIO")) {
                        this->OpenWindow(emu, PIOWindow::Create("PIO", &emu.board.pio));
                    }
                }
                if (!emu.is_device(device::any_z1013)) {
                    if (ImGui::MenuItem("Z80 CTC")) {
                        this->OpenWindow(emu, CTCWindow::Create());
                    }
                }
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Debugging")) {
                if (ImGui::MenuItem("CPU Debugger")) {
                    this->OpenWindow(emu, DebugWindow::Create());
                }
                if (ImGui::MenuItem("Audio Debugger")) {
                    this->OpenWindow(emu, AudioWindow::Create(this->audio));
                }
                if (ImGui::MenuItem("Disassembler")) {
                    this->OpenWindow(emu, DisasmWindow::Create());
                }
                if (ImGui::MenuItem("Memory Editor")) {
                    this->OpenWindow(emu, MemoryWindow::Create());
                }
                if (emu.is_device(device::any_kc85)) {
                    if (ImGui::MenuItem("Scan for Commands...")) {
                        this->OpenWindow(emu, CommandWindow::Create());
                    }
                }
                if (ImGui::BeginMenu("Take Snapshot")) {
                    for (int i = 0; i < SnapshotStorage::MaxNumSnapshots; i++) {
                        strBuilder.Format(32, "Snapshot %d", i);
                        if (ImGui::MenuItem(strBuilder.AsCStr())) {
                            this->snapshotStorage.TakeSnapshot(emu, i);
                        }
                    }
                    ImGui::EndMenu();
                }
                if (this->snapshotStorage.HasSnapshots()) {
                    if (ImGui::BeginMenu("Apply Snapshot")) {
                        for (int i = 0; i < SnapshotStorage::MaxNumSnapshots; i++) {
                            if (this->snapshotStorage.HasSnapshot(i)) {
                                strBuilder.Format(32, "Snapshot %d", i);
                                if (ImGui::MenuItem(strBuilder.AsCStr())) {
                                    this->snapshotStorage.ApplySnapshot(i, emu);
                                }
                            }
                        }
                        ImGui::EndMenu();
                    }
                }
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Settings")) {
                if (ImGui::MenuItem("CRT Effect", nullptr, this->Settings.crtEffect)) {
                    this->Settings.crtEffect = !this->Settings.crtEffect;
                }
                if (ImGui::MenuItem("Color TV", nullptr, this->Settings.colorTV)) {
                    this->Settings.colorTV = !this->Settings.colorTV;
                }
                ImGui::SliderFloat("CRT Warp", &this->Settings.crtWarp, 0.0f, 1.0f/16.0f);
                // FIXME: speed multiplier currently not working
                //ImGui::SliderInt("CPU Speed", &this->Settings.cpuSpeed, 1, 8, "%.0fx");
                if (ImGui::MenuItem("Reset To Defaults")) {
                    this->Settings = settings();
                }
                if (ImGui::MenuItem("Dark UI Theme", nullptr, &this->darkThemeEnabled)) {
                    this->EnableDarkTheme();
                }
                if (ImGui::MenuItem("Light UI Theme", nullptr, &this->lightThemeEnabled)) {
                    this->EnableLightTheme();
                }
                if (ImGui::MenuItem("(DBG) Line-Antialiasing in UI", nullptr, &this->imguiAntiAliasedLines)) {
                    ImGui::GetStyle().AntiAliasedLines = this->imguiAntiAliasedLines;
                    this->darkTheme.AntiAliasedLines = this->imguiAntiAliasedLines;
                    this->lightTheme.AntiAliasedLines = this->imguiAntiAliasedLines;
                }
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }

        // draw open windows
        for (auto& win : this->windows) {
            win->Draw(emu);
        }
    }
    if (this->keyboardWindow) {
        this->keyboardWindow->Draw(emu);
    }
    ImGui::Render();

    // delete closed windows
    for (int i = this->windows.Size() - 1; i >= 0; i--) {
        if (!this->windows[i]->Visible) {
            this->windows.Erase(i);
        }
    }
}

} // namespace YAKC

