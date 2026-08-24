// Reconstructed from PDB debug info.
// Original path : D:\a\GameMaker\GameMaker\GameMaker\Runner\GMS2-Runner-Main\VC_Runner\imgui\imgui_tables.cpp
// Compiled into : D:\a\GameMaker\GameMaker\GameMaker\Runner\GMS2-Runner-Main\VC_Runner\x64\Release-Zeus\imgui_tables.obj
// 49 function symbol(s) attributed to this object.

void ImGuiTable::ImGuiTable(void);
void ImGui::BeginColumns(void *, int32_t, int32_t);
bool ImGui::BeginTableEx(void *, uint32_t, int32_t, int32_t, void *, float);
void ImGui::EndColumns(void);
void ImGui::EndTable(void);
void * ImGui::FindOrCreateColumns(void *, uint32_t);
void ImGui::NextColumn(void);
void ImGui::PopColumnsBackground(void);
void ImGui::PushColumnsBackground(void);
void ImGui::SetColumnOffset(int32_t, float);
void ImGui::SetWindowClipRectBeforeSetChannel(void *, void *);
void ImGui::TableBeginCell(void *, int32_t);
void ImGui::TableDrawBorders(void *);
void ImGui::TableDrawDefaultContextMenu(void *, int32_t);
void ImGui::TableEndCell(void *);
void ImGui::TableEndRow(void *);
void ImGui::TableGcCompactSettings(void);
uint32_t TableGetColumnBorderCol(void *, int32_t, int32_t);
float ImGui::TableGetMaxColumnWidth(void *, int32_t);
void ImGui::TableHeader(void *);
void ImGui::TableHeadersRow(void);
void ImGui::TableLoadSettings(void *);
void ImGui::TableMergeDrawChannels(void *);
bool ImGui::TableNextColumn(void);
void ImGui::TableNextRow(int32_t, float);
void ImGui::TableOpenContextMenu(int32_t);
void ImGui::TablePopBackgroundChannel(void);
void ImGui::TablePushBackgroundChannel(void);
void ImGui::TableSaveSettings(void *);
void ImGui::TableSetBgColor(int32_t, uint32_t, int32_t);
bool ImGui::TableSetColumnIndex(int32_t);
void ImGui::TableSetColumnSortDirection(int32_t, int32_t, bool);
void ImGui::TableSetColumnWidth(int32_t, float);
void * ImGui::TableSettingsCreate(uint32_t, int32_t);
void * ImGui::TableSettingsFindByID(uint32_t);
void TableSettingsHandler_ApplyAll(void *, void *);
void TableSettingsHandler_ClearAll(void *, void *);
void TableSettingsHandler_ReadLine(void *, void *, /* type 0x603 */, void *);
/* type 0x603 */ TableSettingsHandler_ReadOpen(void *, void *, void *);
void TableSettingsHandler_WriteAll(void *, void *, void *);
void TableSettingsInit(void *, uint32_t, int32_t, int32_t);
void TableSetupColumnFlags(void *, void *, int32_t);
void ImGui::TableSetupDrawChannels(void *);
void ImGui::TableSortSpecsBuild(void *);
void ImGui::TableSortSpecsSanitize(void *);
void ImGui::TableUpdateBorders(void *);
void ImGui::TableUpdateColumnsWeightFromWidth(void *);
void ImGui::TableUpdateLayout(void *);
void ImVector<ImGuiOldColumnData>::reserve(int32_t);
