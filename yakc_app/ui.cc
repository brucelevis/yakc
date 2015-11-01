//------------------------------------------------------------------------------
//  ui.cc
//------------------------------------------------------------------------------
#include "ui.h"
#include "util.h"
#include "ui_cpu_window.h"
#include "ui_mem_window.h"
#include "Core/Containers/StaticArray.h"
#include "IMUI/IMUI.h"
#include "Time/Clock.h"
#include "Input/Input.h"

using namespace Oryol;
using namespace yakc;

//------------------------------------------------------------------------------
ui::ui() {
    // empty
}

//------------------------------------------------------------------------------
void
ui::setup(kc85& kc) {
    IMUI::Setup();

    ImGuiStyle& style = ImGui::GetStyle();
    style.WindowRounding = 0.0f;
    style.Alpha = 1.0f;
    style.WindowFillAlphaDefault = 1.0f;
    style.WindowTitleAlign = ImGuiAlign_Center;
    style.Colors[ImGuiCol_WindowBg] = ImVec4(0.25f, 0.25f, 0.25f, 1.0f);

    this->curTime = Clock::Now();
}

//------------------------------------------------------------------------------
void
ui::discard() {
    IMUI::Discard();
}

//------------------------------------------------------------------------------
void
ui::open(const kc85& kc, Ptr<window> win) {
    win->setup(kc);
    this->windows.Add(win);
}

//------------------------------------------------------------------------------
void
ui::onframe(kc85& kc) {
    IMUI::NewFrame(Clock::LapTime(this->curTime));

    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("Computer")) {
            if (ImGui::MenuItem("Power Cycle...")) {
                // FIXME
            }
            if (ImGui::MenuItem("Reset...")) {
                // FIXME
            }
            if (ImGui::MenuItem("Reboot to KC85/3...")) {
                // FIXME
            }
            if (ImGui::MenuItem("Reboot to KC85/4...")) {
                // FIXME
            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Debugger")) {
            if (ImGui::MenuItem("CPU...")) {
                this->open(kc, cpu_window::Create());
            }
            if (ImGui::MenuItem("Memory...")) {
                this->open(kc, mem_window::Create());
            }
            if (ImGui::MenuItem("Assembler...")) {
                // FIXME
            }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }

    // draw open windows
    for (auto& win : this->windows) {
        win->draw(kc);
    }
    ImGui::Render();

    // delete closed windows
    for (int i = this->windows.Size() - 1; i >= 0; i--) {
        if (!this->windows[i]->visible) {
            this->windows.Erase(i);
        }
    }
}
