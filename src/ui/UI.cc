//------------------------------------------------------------------------------
//  UI.cc
//------------------------------------------------------------------------------
#include "UI.h"
#include "ui/Util.h"
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
#include "Time/Clock.h"
#include "Input/Input.h"
#include "Core/String/StringBuilder.h"
#include "roms/roms.h"

using namespace Oryol;
using namespace yakc;

ImVec4 UI::DefaultTextColor;
ImVec4 UI::EnabledColor;
ImVec4 UI::DisabledColor;
ImVec4 UI::EnabledBreakpointColor;
ImVec4 UI::DisabledBreakpointColor;
ImVec4 UI::InvalidOpCodeColor;
ImU32 UI::CanvasTextColor;
ImU32 UI::CanvasLineColor;

//------------------------------------------------------------------------------
void
UI::Setup(kc85& kc) {
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

    this->EnableDarkTheme();

    this->fileLoader.Setup(kc);
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
UI::OpenWindow(kc85& kc, const Ptr<WindowBase>& win) {
    win->Setup(kc);
    this->windows.Add(win);
}

//------------------------------------------------------------------------------
void
UI::EnableDarkTheme() {
    this->darkThemeEnabled = true;
    this->lightThemeEnabled = false;
    ImGui::GetStyle() = this->darkTheme;
    DefaultTextColor = this->darkTheme.Colors[ImGuiCol_Text];
    EnabledColor = ImVec4(0.0f, 1.0f, 0.0f, 1.0f);
    DisabledColor = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
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
    EnabledColor = ImVec4(0.0f, 0.0f, 1.0f, 1.0f);
    DisabledColor = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
    EnabledBreakpointColor = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
    DisabledBreakpointColor = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
    InvalidOpCodeColor = ImVec4(1.0f, 0.0f, 1.0f, 1.0f);
    CanvasTextColor = 0xFF000000;
    CanvasLineColor = 0xFF000000;
}

//------------------------------------------------------------------------------
void
UI::OnFrame(kc85& kc) {
    o_trace_scoped(yakc_ui);

    StringBuilder strBuilder;
    IMUI::NewFrame(Clock::LapTime(this->curTime));
    if (this->uiEnabled) {
        if (ImGui::BeginMainMenuBar()) {
            const char* model;
            switch (kc.model()) {
                case kc85_model::kc85_2: model = "KC85/2"; break;
                case kc85_model::kc85_3: model = "KC85/3"; break;
                case kc85_model::kc85_4: model = "KC85/4"; break;
                default: model="??"; break;
            }
            if (ImGui::BeginMenu(model)) {
                if (ImGui::MenuItem("Load File...")) {
                    auto loadWindow = LoadWindow::Create();
                    loadWindow->SetFileLoader(&this->fileLoader);
                    this->OpenWindow(kc, loadWindow);
                }
                if (ImGui::MenuItem("Power Cycle")) {
                    kc.poweroff();
                    kc.poweron(kc.model(), kc.caos());
                }
                if (ImGui::MenuItem("Reset")) {
                    kc.reset();
                }
                if (ImGui::BeginMenu("Boot to KC85/2")) {
                    if (kc.roms.has(kc85_roms::hc900)) {
                        if (ImGui::MenuItem("HC900-CAOS")) {
                            kc.poweroff();
                            kc.poweron(kc85_model::kc85_2, kc85_caos::caos_hc900);
                        }
                    }
                    if (kc.roms.has(kc85_roms::caos22)) {
                        if (ImGui::MenuItem("HC-CAOS 2.2")) {
                            kc.poweroff();
                            kc.poweron(kc85_model::kc85_2, kc85_caos::caos_2_2);
                        }
                    }
                    ImGui::EndMenu();
                }
                if (ImGui::BeginMenu("Boot to KC85/3")) {
                    if (ImGui::MenuItem("HC-CAOS 3.1")) {
                        kc.poweroff();
                        kc.poweron(kc85_model::kc85_3, kc85_caos::caos_3_1);
                    }
                    if (kc.roms.has(kc85_roms::caos34)) {
                        if (ImGui::MenuItem("HC-CAOS 3.4i")) {
                            kc.poweroff();
                            kc.poweron(kc85_model::kc85_3, kc85_caos::caos_3_4);
                        }
                    }
                    ImGui::EndMenu();
                }
                if (ImGui::BeginMenu("Boot to KC85/4")) {
                    if (kc.roms.has(kc85_roms::caos41c) && kc.roms.has(kc85_roms::caos41e)) {
                        if (ImGui::MenuItem("KC-CAOS 4.1")) {
                            kc.poweroff();
                            kc.poweron(kc85_model::kc85_4, kc85_caos::caos_4_1);
                        }
                    }
                    if (kc.roms.has(kc85_roms::caos42c) && kc.roms.has(kc85_roms::caos42e)) {
                        if (ImGui::MenuItem("KC-CAOS 4.2")) {
                            kc.poweroff();
                            kc.poweron(kc85_model::kc85_4, kc85_caos::caos_4_2);
                        }
                    }
                    ImGui::EndMenu();
                }
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Games")) {
                for (const auto& item : this->fileLoader.Items) {
                    if (int(item.Compat) & int(kc.model())) {
                        if (ImGui::MenuItem(item.Name.AsCStr())) {
                            this->fileLoader.LoadAndStart(kc, item);
                        }
                    }
                }
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Hardware")) {
                if (ImGui::MenuItem("Keyboard")) {
                    this->OpenWindow(kc, KeyboardWindow::Create());
                }
                if (ImGui::MenuItem("Expansion Slots")) {
                    this->OpenWindow(kc, ModuleWindow::Create());
                }
                if (ImGui::MenuItem("Memory Map")) {
                    this->OpenWindow(kc, MemoryMapWindow::Create());
                }
                if (ImGui::MenuItem("Z80 PIO")) {
                    this->OpenWindow(kc, PIOWindow::Create());
                }
                if (ImGui::MenuItem("Z80 CTC")) {
                    this->OpenWindow(kc, CTCWindow::Create());
                }
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Debugging")) {
                if (ImGui::MenuItem("Debugger")) {
                    this->OpenWindow(kc, DebugWindow::Create());
                }
                if (ImGui::MenuItem("Disassembler")) {
                    this->OpenWindow(kc, DisasmWindow::Create());
                }
                if (ImGui::MenuItem("Memory Editor")) {
                    this->OpenWindow(kc, MemoryWindow::Create());
                }
                if (ImGui::MenuItem("Scan for Commands...")) {
                    this->OpenWindow(kc, CommandWindow::Create());
                }
                if (ImGui::BeginMenu("Take Snapshot")) {
                    for (int i = 0; i < SnapshotStorage::MaxNumSnapshots; i++) {
                        strBuilder.Format(32, "Snapshot %d", i);
                        if (ImGui::MenuItem(strBuilder.AsCStr())) {
                            this->snapshotStorage.TakeSnapshot(kc, i);
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
                                    this->snapshotStorage.ApplySnapshot(i, kc);
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
                ImGui::SliderInt("CPU Speed", &this->Settings.cpuSpeed, 1, 8, "%.0fx");
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
            win->Draw(kc);
        }
    }
    else {
        // if UI is disabled, draw a simple overlay with help on how to toggle UI
        if (helpOpen) {
            ImGui::SetNextWindowPosCenter();
            if (ImGui::Begin("Help", &this->helpOpen, ImVec2(0,0), 0.75f, ImGuiWindowFlags_NoTitleBar|ImGuiWindowFlags_NoResize|ImGuiWindowFlags_ShowBorders))
            {
                ImGui::Text("Press TAB or double-tap to toggle UI!");
                ImGui::Dummy(ImVec2(96,0)); ImGui::SameLine();
                if (ImGui::Button("Got it!")) {
                    this->helpOpen = false;
                }
            }
            ImGui::End();
        }
    }
    ImGui::Render();

    // delete closed windows
    for (int i = this->windows.Size() - 1; i >= 0; i--) {
        if (!this->windows[i]->Visible) {
            this->windows.Erase(i);
        }
    }
}
