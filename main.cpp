#include <iostream>
#include <fstream>
#include <string>
#include <nlohmann/json.hpp>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include "SortTable.h"
#include "TreeTable.h"
#include "MatchValue.h"

using json = nlohmann::json;

void load_data(SortTable& sortdb) {
    std::ifstream file("database.json");
    if (!file.is_open()) return;
    json data;
    try { file >> data; } catch (...) { return; }
    file.close();

    for (auto& item : data) {
        std::string date = "TBD";
        if (item.contains("begin_at") && item["begin_at"].is_string()) {
            date = item["begin_at"].get<std::string>();
        }

        std::string t1 = "TBD", t2 = "TBD", score = "0-0";
        
        if (item.contains("opponents") && item["opponents"].is_array() && item["opponents"].size() >= 2) {
            auto& opp1 = item["opponents"][0]["opponent"];
            auto& opp2 = item["opponents"][1]["opponent"];
            
            if (opp1.contains("name") && opp1["name"].is_string()) {
                t1 = opp1["name"].get<std::string>();
            }
            if (opp2.contains("name") && opp2["name"].is_string()) {
                t2 = opp2["name"].get<std::string>();
            }
        }
        
        if (item.contains("results") && item["results"].is_array() && item["results"].size() >= 2) {
            score = std::to_string((int)item["results"][0]["score"]) + "-" + 
                    std::to_string((int)item["results"][1]["score"]);
        }
        
        sortdb.InsertRecord(date, new MatchValue(date, t1, t2, score));
    }
}

int main() {
    if (!glfwInit()) return 1;
    GLFWwindow* window = glfwCreateWindow(1280, 720, "HLTV Parser", NULL, NULL);
    glfwMakeContextCurrent(window);
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    SortTable sortdb(Insert, 100000);
    load_data(sortdb);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        ImGui_ImplOpenGL3_NewFrame(); ImGui_ImplGlfw_NewFrame(); ImGui::NewFrame();
        ImGui::Begin("Matches Database");
        if (ImGui::BeginTable("matches", 4, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg)) {
            ImGui::TableSetupColumn("Date"); ImGui::TableSetupColumn("Team 1");
            ImGui::TableSetupColumn("Team 2"); ImGui::TableSetupColumn("Score");
            ImGui::TableHeadersRow();

            sortdb.Reset();
            while (!sortdb.IsTabEnd()) {
                MatchValue* m = dynamic_cast<MatchValue*>(sortdb.GetValue());
                if (m) {
                    ImGui::TableNextRow();
                    ImGui::TableSetColumnIndex(0); ImGui::Text("%s", m->date.c_str());
                    ImGui::TableSetColumnIndex(1); ImGui::Text("%s", m->team1.c_str());
                    ImGui::TableSetColumnIndex(2); ImGui::Text("%s", m->team2.c_str());
                    ImGui::TableSetColumnIndex(3); ImGui::Text("%s", m->score.c_str());
                }
                sortdb.GoNext();
            }
            ImGui::EndTable();
        }
        ImGui::End();
        ImGui::Render();
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}