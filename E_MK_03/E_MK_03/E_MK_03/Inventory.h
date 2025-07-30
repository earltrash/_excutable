#pragma once
#include "pch.h"
#include "Object.h"
#include "BitmapManager.h"
#include "UIUtility.h"
#include "Renderer.h"

enum class ItemType
{
    ARMOR,       // 방어구
    CONSUMABLE,  // 소모품
    MATERIAL     // 재료
};

struct  ItemData
{
    int itemId;                                       // 아이템 고유 키
    std::string name;                                 // 이름
    std::string description;                          // 설명
    std::string iconTexture;                          // 텍스처 키
    int maxCount;                                     // 최대 갯수(장비는 1)
    bool isSynthesis;                                 // 합성 가능 여부
    bool isEnforce;                                   // 강화 가능 여부
    std::unordered_map<std::string, float> stats;     // 능력치 (공격력, 방어력 등)
    std::vector<std::string> effects;                 // 특수 효과들
    ItemType type;

    ItemData(int id, const std::string& name, const std::string& desc,
        const std::string& icon, int stack = 1, bool synthesis = false, bool enforce = false, ItemType itemType = ItemType::MATERIAL) // isSynthesis, isEnforce 기본값 추가
        : itemId(id), name(name), description(desc), iconTexture(icon),
        maxCount(stack), isSynthesis(synthesis), isEnforce(enforce), type(itemType) {}

    // 스택 가능한지 확인
    bool IsStackable() const
    {
        return maxCount > 1;
    }

    // 장비 아이템인지 확인
    bool IsEquipment() const
    {
        return type == ItemType::ARMOR;
    }

    // 소모품인지 확인
    bool IsConsumable() const
    {
        return type == ItemType::CONSUMABLE;
    }

    // 재료템인지 확인 (중복된 IsConsumable()을 IsMaterial()로 변경)
    bool IsMaterial() const
    {
        return type == ItemType::MATERIAL;
    }

    // 능력치 추가/수정
    void SetStat(const std::string& statName, float value)
    {
        stats[statName] = value;
    }

    // 능력치 조회
    float GetStat(const std::string& statName) const
    {
        auto it = stats.find(statName);
        return it != stats.end() ? it->second : 0.0f;
    }

    // 특수 효과 추가
    void AddEffect(const std::string& effect)
    {
        effects.push_back(effect);
    }

    // 디버깅용
    void PrintInfo() const
    {
        std::cout << "=== Item Info ===" << std::endl;
        std::cout << "ID: " << itemId << std::endl;
        std::cout << "Name: " << name << std::endl;
        std::cout << "Description: " << description << std::endl;
        std::cout << "Max Stack: " << maxCount << std::endl;
        std::cout << "Type: " << (type == ItemType::ARMOR ? "Armor" : (type == ItemType::CONSUMABLE ? "Consumable" : "Material")) << std::endl;
    }
};

// 아이템 인스턴스
struct ItemInstance
{
    int itemId;
    int count;

    ItemInstance(int id = 0, int cnt = 0) : itemId(id), count(cnt) {}
    bool IsEmpty() const { return itemId == 0 || count == 0; }
};

// 아이템 데이터베이스
class ItemDatabase
{
public:
    void AddItemData(std::unique_ptr<ItemData> itemData)
    {
        itemDataMap[itemData->itemId] = std::move(itemData);
    }

    const ItemData* GetItemData(int itemId) const
    {
        auto it = itemDataMap.find(itemId);
        return it != itemDataMap.end() ? it->second.get() : nullptr;
    }
private:
    std::unordered_map<int, std::unique_ptr<ItemData>> itemDataMap; 
};

// Direct2D 렌더링 정보를 가진 UI 스프라이트
struct UIBitmap
{
    ID2D1Bitmap* bitmap;           // Direct2D 비트맵
    Rect srcRect;                  // 소스 영역 (스프라이트 시트용)
    Vec2 position;                 // 렌더링 위치
    Vec2 size;                     // 렌더링 크기
    float opacity;                 // 투명도

    UIBitmap() : bitmap(nullptr), opacity(1.0f) {}
};

class InventorySlot
{
public:
    ItemInstance item;             // 실제 아이템 데이터 (ID, 개수)
    bool isEnabled;

    UIBitmap backgroundBitmap;     // 슬롯 배경 비트맵
    UIBitmap itemBitmap;           // 아이템 아이콘 비트맵
    UIBitmap overlayBitmap;        // 호버/선택 효과 비트맵

    // UI용
    Rect bounds;
    bool isHovered;
    bool isSelected;

    InventorySlot() : isEnabled(true), isHovered(false), isSelected(false) {}

    void SetBounds(const Rect& rect)
    {
        bounds = rect;

        // 배경 비트맵 설정
        backgroundBitmap.position = Vec2(rect.x, rect.y);
        backgroundBitmap.size = Vec2(rect.width, rect.height);

        // 아이템 비트맵 설정 (패딩 적용)
        float padding = 4.0f;
        itemBitmap.position = Vec2(rect.x + padding, rect.y + padding);
        itemBitmap.size = Vec2(rect.width - padding * 2, rect.height - padding * 2);

        // 오버레이 설정
        overlayBitmap.position = Vec2(rect.x, rect.y);
        overlayBitmap.size = Vec2(rect.width, rect.height);
    }

    // === 핵심 연결 함수 ===
    void UpdateItemBitmap(BitmapManager* bitmapManager, const ItemDatabase* itemDB)
    {
        if (!item.IsEmpty()) 
        {
            // 1. 아이템 데이터 조회
            const ItemData* data = itemDB->GetItemData(item.itemId);
            if (data)
            {
                // 2. 비트맵 설정 (아이템 아이콘)
                itemBitmap.bitmap = bitmapManager->GetBitmap(data->iconTexture);
                itemBitmap.srcRect = Rect(0, 0, 48, 48);  // 전체 아이콘 사용 (예시임. 실제 이미지 사이즈에 따라 조절.)
                itemBitmap.opacity = 1.0f;
            }
            else
            {
                itemBitmap.bitmap = nullptr; // 아이템 데이터가 없으면 비트맵을 비움
            }
        }
        else
        {
            // 빈 슬롯일 경우 empty_slot_item 비트맵을 사용
            itemBitmap.bitmap = bitmapManager->GetBitmap("slot_normal"); // 빈 슬롯용 이미지 키
            itemBitmap.srcRect = Rect(0, 0, 48, 48); // 기본 크기
            itemBitmap.opacity = 1.0f;
        }
    }

    void UpdateBackgroundBitmap(BitmapManager* bitmapManager)
    {
        std::string bgKey;
        if (!isEnabled)
        {
            bgKey = "slot_disabled";
        }
        else if (isHovered)
        {
            bgKey = "slot_hover";
        }
        else if (isSelected)
        {
            bgKey = "slot_selected";
        }
        else
        {
            bgKey = "slot_normal";
        }

        std::cout << "슬롯 배경 키: " << bgKey << std::endl;

        backgroundBitmap.bitmap = bitmapManager->GetBitmap(bgKey);
        backgroundBitmap.srcRect = Rect(0, 0, 48, 48);  // 슬롯 크기 (예시)
    }

    bool IsEmpty() const { return item.IsEmpty(); }

    void SetItem(int itemId, int count)
    {
        item.itemId = itemId;
        item.count = count;
    }

    void Clear()
    {
        item = ItemInstance();
    }
};

class Inventory
{
public:
    Inventory(ItemDatabase* itemDB, BitmapManager* bmpManager, ID2D1RenderTarget* rt)
        : itemDatabase(itemDB), bitmapManager(bmpManager), renderTarget(rt), isWindowActive(true),
        isWindowDragging(false), showTooltip(false), textFormat(nullptr), textBrush(nullptr)
    {
        InitializeWindowBounds();     // 윈도우 바운드 초기화 (regions보다 먼저)
        InitializeRegions();          // 영역 초기화
        LoadUIBitmaps();              // 이미지 로드해서 가져오기
        InitializeSlots();            // 슬롯 초기화
        InitializeTextRendering();    // 텍스트 렌더링 초기화

        dragState.isDragging = false; // 드래그 상태 초기화
    }

    ~Inventory() // 소멸자에서 DirectWrite 자원 해제
    {
        SafeRelease(&textFormat);
        SafeRelease(&textBrush);
    }

    // 인벤토리 구조
    struct Region
    {
        int id;
        bool isEnabled;
        Rect bounds;
        Vec2 gridSize;  // 4x8
    };
    std::vector<Region> regions;

    // 드래그 상태
    struct DragState
    {
        bool isDragging;
        InventorySlot* sourceSlot;
        ItemInstance draggedItem;
        Vec2 mousePos;
        UIBitmap dragBitmap;  // 드래그 중인 아이템 비트맵
    } dragState;

    // 텍스트 렌더링을 위한 DWrite 객체 (공용)
    IDWriteTextFormat* textFormat;
    ID2D1SolidColorBrush* textBrush;
    ID2D1RenderTarget* renderTarget; // 텍스트 브러시 생성용

    void InitializeWindowBounds()
    {
        float slotSize = 48.0f;
        float padding = 4.0f;
        float totalSlotDimension = slotSize + padding + 3.0f;  // 추가 여백 계산

        // 전체 윈도우 크기 계산 (12x8 그리드를 모두 포함 + 여백 + 타이틀바 공간)
        float totalGridWidth = 12 * totalSlotDimension;
        float totalGridHeight = 8 * totalSlotDimension;

        // 초기 윈도우 위치 및 크기 설정
        windowBounds = Rect(
            20.0f, // 좌측 여백
            50.0f, // 상단 여백 (타이틀바 공간)
            totalGridWidth + 40.0f, // 좌우 여백 합산 (20 + totalGridWidth + 20)
            totalGridHeight + 60.0f // 상하 여백 합산 (50 + totalGridHeight + 10)
        );
        windowPosition = Vec2(windowBounds.x, windowBounds.y); // 초기 위치 설정

        // 타이틀바 영역 설정 (창 위치에 상대적)
        titleBarBounds = Rect(windowPosition.x, windowPosition.y, windowBounds.width, 30.0f);

        // 닫기 버튼 영역 설정 (오른쪽 상단, 창 위치에 상대적)
        float closeButtonSize = 22.0f;
        closeButtonBounds = Rect(
            windowPosition.x + windowBounds.width - closeButtonSize - 5,
            windowPosition.y + 5,
            closeButtonSize,
            closeButtonSize
        );

        // 윈도우 배경 비트맵의 렌더링 위치/크기 설정
        windowBackground.position = windowPosition;
        windowBackground.size = Vec2(windowBounds.width, windowBounds.height);
        windowBackground.srcRect = Rect(0, 0, windowBounds.width, windowBounds.height); // 실제 이미지 크기

        // 닫기 버튼 비트맵의 렌더링 위치/크기 설정
        closeButton.position = Vec2(closeButtonBounds.x, closeButtonBounds.y);
        closeButton.size = Vec2(closeButtonBounds.width, closeButtonBounds.height);
        closeButton.srcRect = Rect(0, 0, 27, 27); // 닫기 버튼 이미지 크기
    }

    void InitializeRegions()
    {
        regions.resize(3); // 3개의 영역 (4x8, 4x8, 4x8)

        float slotSize = 48.0f;
        float padding = 4.0f;
        float totalSlotDimension = slotSize + padding;

        // windowBounds의 내부 영역을 기준으로 배치
        float currentRegionX = windowPosition.x + 23.0f; // 윈도우 좌측 여백

        // Region 0: 기본 해금 영역 (4x8)
        regions[0].id = 0;
        regions[0].isEnabled = true;
        regions[0].gridSize = Vec2(4, 8);
        regions[0].bounds = Rect(
            currentRegionX,
            windowPosition.y + 50.0f, // 윈도우 상단 여백 + 타이틀바 공간
            regions[0].gridSize.x * totalSlotDimension,
            regions[0].gridSize.y * totalSlotDimension
        );
        currentRegionX += regions[0].bounds.width + 23.0f; // 다음 영역 시작 X

        // Region 1: 중간 잠금 영역 (4x8)
        regions[1].id = 1;
        regions[1].isEnabled = false; // 잠금
        regions[1].gridSize = Vec2(4, 8);
        regions[1].bounds = Rect(
            currentRegionX,
            windowPosition.y + 50.0f,
            regions[1].gridSize.x * totalSlotDimension,
            regions[1].gridSize.y * totalSlotDimension
        );
        currentRegionX += regions[1].bounds.width + 15.0f;

        // Region 2: 오른쪽 잠금 영역 (4x8)
        regions[2].id = 2;
        regions[2].isEnabled = false; // 잠금
        regions[2].gridSize = Vec2(4, 8);
        regions[2].bounds = Rect(
            currentRegionX,
            windowPosition.y + 50.0f,
            regions[2].gridSize.x * totalSlotDimension,
            regions[2].gridSize.y * totalSlotDimension
        );
    }

    void InitializeSlots()
    {
        float slotSize = 48.0f;
        float padding = 4.0f;
        float totalSlotDimension = slotSize + padding;

        for (int regionId = 0; regionId < regions.size(); ++regionId)
        {
            const Region& region = regions[regionId];

            for (int y = 0; y < region.gridSize.y; ++y)
            {
                for (int x = 0; x < region.gridSize.x; ++x)
                {
                    int slotIndex = y * region.gridSize.x + x;
                    std::pair<int, int> key = { regionId, slotIndex };

                    InventorySlot& slot = slots[key];

                    // 슬롯 위치는 해당 Region의 bounds를 기준으로 계산
                    float slotX = region.bounds.x + x * totalSlotDimension;
                    float slotY = region.bounds.y + y * totalSlotDimension;

                    slot.SetBounds(Rect(slotX, slotY, slotSize, slotSize));
                    slot.isEnabled = region.isEnabled; // 영역의 활성화 상태에 따라 슬롯 활성화 설정
                    slot.UpdateBackgroundBitmap(bitmapManager); // 초기 배경 설정
                }
            }
        }
    }

    void LoadUIBitmaps()
    {
        // UI 비트맵들 로드 이미지 싹 가져오고 
        bitmapManager->LoadBitmap("Resource/ui/Slot.png",  "slot_normal");    
        bitmapManager->LoadBitmap("Resource/ui/Slot.png",  "slot_hover");
        bitmapManager->LoadBitmap("Resource/ui/Slot.png",  "slot_disabled");
        bitmapManager->LoadBitmap("Resource/ui/Slot.png",  "slot_selected");
        bitmapManager->LoadBitmap("Resource/ui/Player.png", "window_bg");
        bitmapManager->LoadBitmap("Resource/ui/CloseButton.png",   "close_button");
        bitmapManager->LoadBitmap("Resource/ui/Player.png", "tooltip_background"); 

        ID2D1Bitmap* slotNormal = bitmapManager->GetBitmap("slot_normal");
        ID2D1Bitmap* windowBg = bitmapManager->GetBitmap("window_bg");
        ID2D1Bitmap* closeBtn = bitmapManager->GetBitmap("close_button");

        std::cout << "slot_normal: " << (slotNormal ? "로딩 성공" : "로딩 실패") << std::endl;
        std::cout << "window_bg: " << (windowBg ? "로딩 성공" : "로딩 실패") << std::endl;
        std::cout << "close_button: " << (closeBtn ? "로딩 성공" : "로딩 실패") << std::endl;

        windowBackground.bitmap = bitmapManager->GetBitmap("window_bg");
        closeButton.bitmap = bitmapManager->GetBitmap("close_button");
        tooltipBackground.bitmap = bitmapManager->GetBitmap("tooltip_background");
        tooltipBackground.srcRect = Rect(0, 0, 100, 60); // 예시임. 툴팁 배경 크기

        std::cout << "=== 비트맵 로딩 완료 ===" << std::endl;
    }

    void InitializeTextRendering()
    {
        IDWriteFactory* dwriteFactory = nullptr;
        HRESULT hr = DWriteCreateFactory(
            DWRITE_FACTORY_TYPE_SHARED,
            __uuidof(IDWriteFactory),
            reinterpret_cast<IUnknown**>(&dwriteFactory)
        );

        if (SUCCEEDED(hr))
        {
            hr = dwriteFactory->CreateTextFormat(
                L"Arial",
                nullptr,
                DWRITE_FONT_WEIGHT_NORMAL,
                DWRITE_FONT_STYLE_NORMAL,
                DWRITE_FONT_STRETCH_NORMAL,
                14.0f,
                L"ko-kr",
                &textFormat
            );
        }

        SafeRelease(&dwriteFactory);

        if (renderTarget)
        {
            renderTarget->CreateSolidColorBrush(
                D2D1::ColorF(D2D1::ColorF::White),
                &textBrush
            );
        }

    }

    // 아이템 추가 (데이터 + UI 자동 연결)
    bool AddItem(int itemId, int count = 1)
    {
        const ItemData* itemData = itemDatabase->GetItemData(itemId);
        if (!itemData) return false;

        // 빈 슬롯 찾기
        for (auto& [key, slot] : slots)
        {
            if (!slot.isEnabled) continue; // 비활성화된 슬롯에는 추가 불가

            // 스택 가능한 아이템이라면 기존 슬롯에 합치기 시도 (예시)
            if (itemData->IsStackable() && slot.item.itemId == itemId && (slot.item.count + count) <= itemData->maxCount)
            {
                slot.item.count += count;
                slot.UpdateItemBitmap(bitmapManager, itemDatabase); // 개수 변경은 비트맵 변경이 없지만, 혹시 모를 경우 호출
                return true;
            }

            if (slot.IsEmpty()) {
                slot.SetItem(itemId, count);
                slot.UpdateItemBitmap(bitmapManager, itemDatabase);
                return true;
            }
        }
        return false;
    }

    // 영역 해금 함수
    void UnlockRegion(int regionId)
    {
        if (regionId >= 0 && regionId < regions.size())
        {
            regions[regionId].isEnabled = true;
            for (int y = 0; y < regions[regionId].gridSize.y; ++y)
            {
                for (int x = 0; x < regions[regionId].gridSize.x; ++x)
                {
                    int slotIndex = y * regions[regionId].gridSize.x + x;
                    std::pair<int, int> key = { regionId, slotIndex };
                    if (slots.count(key))
                    {
                        slots[key].isEnabled = true;
                        slots[key].UpdateBackgroundBitmap(bitmapManager);
                    }
                }
            }
        }
    }

    // 마우스 이벤트 처리
    void HandleMouseMove(const Vec2& mousePos)
    {
        if (!isWindowActive)
        {
            showTooltip = false;
            return;
        }

        // 윈도우 드래그 중일 때
        if (isWindowDragging)
        {
            float deltaX = mousePos.x - dragStartMousePos.x;
            float deltaY = mousePos.y - dragStartMousePos.y;
            windowPosition = Vec2(dragStartWindowPos.x + deltaX, dragStartWindowPos.y + deltaY);

            // 윈도우 바운드, 타이틀바, 닫기 버튼 바운드 업데이트
            windowBounds.x = windowPosition.x;
            windowBounds.y = windowPosition.y;
            titleBarBounds.x = windowPosition.x;
            titleBarBounds.y = windowPosition.y;
            closeButtonBounds.x = windowPosition.x + windowBounds.width - closeButtonBounds.width - 5;
            closeButtonBounds.y = windowPosition.y + 5;

            // 슬롯들의 위치도 업데이트해야 함
            UpdateSlotPositions();
        }
        else // 윈도우 드래그 중이 아닐 때만 슬롯 호버 및 툴팁 처리
        {
            showTooltip = false;
            InventorySlot* hoveredSlot = nullptr;

            // 슬롯 호버 상태 업데이트
            for (auto& [key, slot] : slots)
            {
                bool wasHovered = slot.isHovered;
                // 슬롯의 현재 렌더링 위치(이동된 창에 따라 달라짐)를 기준으로 Contains 체크
                // slot.bounds는 이미 UpdateSlotPositions에 의해 현재 창 위치에 맞게 업데이트됨 (혹은 이미 초기화 시 올바르게 설정됨)
                slot.isHovered = slot.bounds.Contains(mousePos);

                if (wasHovered != slot.isHovered)
                {
                    slot.UpdateBackgroundBitmap(bitmapManager);
                }

                if (slot.isHovered && !slot.IsEmpty())
                {
                    hoveredSlot = &slot; // 현재 마우스가 올라간 슬롯
                }
            }

            // 툴팁 정보 업데이트
            if (hoveredSlot)
            {
                const ItemData* data = itemDatabase->GetItemData(hoveredSlot->item.itemId);
                if (data)
                {
                    currentHoveredItemName = data->name;
                    currentHoveredItemDescription = data->description;
                    currentHoveredItemCount = hoveredSlot->item.count;
                    // 툴팁 위치는 마우스 커서 옆으로 조정 (창이 이동해도 상대적으로 유지)
                    tooltipPosition = Vec2(mousePos.x + 15, mousePos.y + 15);
                    showTooltip = true;
                }
            }
        }

        // 아이템 드래그 중일 때 (마우스 위치 업데이트)
        if (dragState.isDragging)
        {
            dragState.mousePos = mousePos;
        }
    }
    
    void HandleMouseDown(const Vec2& mousePos)
    {
        if (!isWindowActive) return;

        // 닫기 버튼 클릭 처리
        if (closeButtonBounds.Contains(mousePos))
        {
            isWindowActive = false; // 창 비활성화
            showTooltip = false; // 툴팁 숨김
            return;
        }

        // 타이틀바 드래그 시작
        if (titleBarBounds.Contains(mousePos))
        {
            isWindowDragging = true;
            dragStartMousePos = mousePos;
            dragStartWindowPos = windowPosition;
            return; // 타이틀바 드래그 시작 시 다른 클릭 이벤트는 무시
        }

        // 슬롯 드래그 시작 (기존 로직)
        InventorySlot* slot = GetSlotAt(mousePos); // 현재 창 위치를 고려하여 슬롯 가져오기
        if (slot && !slot->IsEmpty() && slot->isEnabled)
        {
            dragState.isDragging = true;
            dragState.sourceSlot = slot;
            dragState.draggedItem = slot->item;
            dragState.mousePos = mousePos;

            const ItemData* itemData = itemDatabase->GetItemData(slot->item.itemId);
            if (itemData)
            {
                dragState.dragBitmap.bitmap = bitmapManager->GetBitmap(itemData->iconTexture);
                dragState.dragBitmap.size = Vec2(48, 48);
            }

            slot->Clear();
            slot->UpdateItemBitmap(bitmapManager, itemDatabase);
        }
    }

    void HandleMouseUp(const Vec2& mousePos)
    {
        if (!isWindowActive) return;

        // 윈도우 드래그 종료
        if (isWindowDragging)
        {
            isWindowDragging = false;
            return;
        }

        // 아이템 드래그 종료
        if (!dragState.isDragging) return;

        bool placed = false;
        InventorySlot* targetSlot = GetSlotAt(mousePos); // 현재 마우스 위치의 슬롯을 다시 찾음

        if (targetSlot && targetSlot->isEnabled)
        {
            // 스택 가능한 아이템이라면 합치기 시도
            const ItemData* draggedItemData = itemDatabase->GetItemData(dragState.draggedItem.itemId);
            if (draggedItemData && draggedItemData->IsStackable() &&
                targetSlot->item.itemId == dragState.draggedItem.itemId &&
                (targetSlot->item.count + dragState.draggedItem.count) <= draggedItemData->maxCount)
            {
                targetSlot->item.count += dragState.draggedItem.count;
                targetSlot->UpdateItemBitmap(bitmapManager, itemDatabase);
                placed = true;
            }
            else if (targetSlot->IsEmpty())
            {
                // 빈 슬롯에 드롭
                targetSlot->item = dragState.draggedItem;
                targetSlot->UpdateItemBitmap(bitmapManager, itemDatabase);
                placed = true;
            }
            else
            {
                // 다른 아이템이 있는 슬롯에 드롭 (교환 로직 추가 가능)
                // 현재는 그냥 원래 위치로 되돌림
            }
        }

        // 배치 실패시 원래 위치로 복귀
        if (!placed)
        {
            dragState.sourceSlot->item = dragState.draggedItem;
            dragState.sourceSlot->UpdateItemBitmap(bitmapManager, itemDatabase);
        }

        dragState.isDragging = false;
    }

    // 창이 이동할 때 슬롯들의 실제 렌더링 위치를 업데이트합니다.
    void UpdateSlotPositions()
    {
        float slotSize = 48.0f;
        float padding = 4.0f;
        float totalSlotDimension = slotSize + padding;

        for (int regionId = 0; regionId < regions.size(); ++regionId)
        {
            const Region& region = regions[regionId];

            for (int y = 0; y < region.gridSize.y; ++y)
            {
                for (int x = 0; x < region.gridSize.x; ++x)
                {
                    int slotIndex = y * region.gridSize.x + x;
                    std::pair<int, int> key = { regionId, slotIndex };

                    if (slots.count(key))
                    {
                        InventorySlot& slot = slots[key];

                        // 슬롯 위치는 해당 Region의 bounds를 기준으로 계산 (regions.bounds는 InitializeRegions에서 windowPosition에 따라 이미 결정됨)
                        float slotX = region.bounds.x + x * totalSlotDimension;
                        float slotY = region.bounds.y + y * totalSlotDimension;

                        slot.SetBounds(Rect(slotX, slotY, slotSize, slotSize));
                    }
                }
            }
        }
    }

    // === 기존 렌더링 방식에 맞춘 렌더링 함수 ===
    void Render(ID2D1RenderTarget* renderTarget)
    {
        if (!isWindowActive) return;

        // 1. 윈도우 배경 렌더링
        if (windowBackground.bitmap)
        {
            D2D1_RECT_F destRect = D2D1::RectF(
                windowPosition.x, windowPosition.y,
                windowPosition.x + windowBounds.width, windowPosition.y + windowBounds.height
            );
            D2D1_RECT_F srcRect = windowBackground.srcRect.ToD2DRect();

            renderTarget->DrawBitmap(windowBackground.bitmap, destRect, windowBackground.opacity,
                D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, srcRect);
        }

        // 2. 타이틀바 및 닫기 버튼 렌더링
        RenderTitleBar(renderTarget);
        RenderCloseButton(renderTarget);

        // 3. 모든 슬롯 렌더링
        for (const auto& [key, slot] : slots)
        {
            RenderSlot(renderTarget, slot);
        }

        // 4. 드래그 중인 아이템 렌더링
        if (dragState.isDragging && dragState.dragBitmap.bitmap)
        {
            D2D1_RECT_F dragDestRect = D2D1::RectF(
                dragState.mousePos.x - dragState.dragBitmap.size.x / 2.0f, // 마우스 중앙에 오도록
                dragState.mousePos.y - dragState.dragBitmap.size.y / 2.0f,
                dragState.mousePos.x + dragState.dragBitmap.size.x / 2.0f,
                dragState.mousePos.y + dragState.dragBitmap.size.y / 2.0f
            );
            renderTarget->DrawBitmap(dragState.dragBitmap.bitmap, dragDestRect, 0.8f);
        }

        // 5. 툴팁 렌더링 (가장 마지막에 렌더링하여 다른 UI 위에 표시)
        if (showTooltip)
        {
            RenderTooltip(renderTarget);
        }
    }

    void RenderSlot(ID2D1RenderTarget* renderTarget, const InventorySlot& slot)
    {
        std::cout << "=== RenderSlot 호출 ===" << std::endl;
        std::cout << "slot.isEnabled: " << (slot.isEnabled ? "true" : "false") << std::endl;
        std::cout << "slot.backgroundBitmap.bitmap: " << (slot.backgroundBitmap.bitmap ? "있음" : "nullptr") << std::endl;

        // 1. 슬롯 배경 렌더링 (슬롯의 bounds는 이미 UpdateSlotPositions에 의해 현재 창 위치에 맞게 업데이트됨)
        if (slot.backgroundBitmap.bitmap)
        {
            std::cout << "배경 비트맵 렌더링 시도" << std::endl;

            D2D1_RECT_F destRect = slot.bounds.ToD2DRect();
            D2D1_RECT_F srcRect = slot.backgroundBitmap.srcRect.ToD2DRect();
            renderTarget->DrawBitmap(slot.backgroundBitmap.bitmap, destRect,
                slot.backgroundBitmap.opacity,
                D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, srcRect);

            std::cout << "배경 비트맵 렌더링 완료" << std::endl;
        }

        // 비활성화된 슬롯은 빈slot이미지 그림.
        if (!slot.isEnabled)
        {
            std::cout << "비활성화된 슬롯이므로 배경만 렌더링하고 종료" << std::endl;
            return;
        }

        // 2. 아이템 아이콘 렌더링
        if (!slot.IsEmpty() && slot.itemBitmap.bitmap)
        {
            D2D1_RECT_F itemDestRect = D2D1::RectF(
                slot.itemBitmap.position.x, // itemBitmap.position은 SetBounds에서 이미 슬롯 bounds에 맞춰 설정됨
                slot.itemBitmap.position.y,
                slot.itemBitmap.position.x + slot.itemBitmap.size.x,
                slot.itemBitmap.position.y + slot.itemBitmap.size.y
            );
            D2D1_RECT_F itemSrcRect = slot.itemBitmap.srcRect.ToD2DRect();

            renderTarget->DrawBitmap(slot.itemBitmap.bitmap, itemDestRect,
                slot.itemBitmap.opacity,
                D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, itemSrcRect);

            // 3. 아이템 개수 텍스트
            if (slot.item.count > 1 && textFormat && textBrush)
            {
                std::wstring countText = std::to_wstring(slot.item.count);
                // 텍스트 위치를 슬롯 우측 하단에 배치 (예시)
                D2D1_RECT_F textRect = D2D1::RectF(
                    slot.bounds.x + slot.bounds.width - 30, // 우측 정렬
                    slot.bounds.y + slot.bounds.height - 20, // 하단 정렬
                    slot.bounds.x + slot.bounds.width,
                    slot.bounds.y + slot.bounds.height
                );
                renderTarget->DrawText(
                    countText.c_str(),
                    static_cast<UINT32>(countText.length()),
                    textFormat,
                    textRect,
                    textBrush
                );
            }
        }
    }

    void RenderTitleBar(ID2D1RenderTarget* renderTarget)
    {
        ID2D1SolidColorBrush* brush = nullptr;
        renderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::DarkSlateGray, 0.7f), &brush);
        if (brush)
        {
            // 타이틀바 영역은 windowPosition에 따라 이미 업데이트됨
            D2D1_RECT_F rect = titleBarBounds.ToD2DRect();
            renderTarget->FillRectangle(rect, brush);
            SafeRelease(&brush);
        }

        if (textFormat && textBrush)
        {
            renderTarget->DrawText(
                L"Inventory",
                static_cast<UINT32>(wcslen(L"Inventory")),
                textFormat,
                D2D1::RectF(titleBarBounds.x + 10, titleBarBounds.y + 5,
                    titleBarBounds.x + titleBarBounds.width - 10,
                    titleBarBounds.y + titleBarBounds.height - 5),
                textBrush
            );
        }
    }

    void RenderCloseButton(ID2D1RenderTarget* renderTarget)
    {
        if (closeButton.bitmap)
        {
            // 닫기 버튼 위치는 closeButtonBounds에 이미 업데이트됨
            D2D1_RECT_F destRect = closeButtonBounds.ToD2DRect();
            D2D1_RECT_F srcRect = closeButton.srcRect.ToD2DRect();
            renderTarget->DrawBitmap(closeButton.bitmap, destRect, closeButton.opacity,
                D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, srcRect);
        }
    }

    void RenderTooltip(ID2D1RenderTarget* renderTarget)
    {
        if (!tooltipBackground.bitmap || !textFormat || !textBrush) return;

        // 툴팁 배경 렌더링
        D2D1_RECT_F tooltipDestRect = D2D1::RectF(
            tooltipPosition.x,
            tooltipPosition.y,
            tooltipPosition.x + tooltipBackground.srcRect.width,
            tooltipPosition.y + tooltipBackground.srcRect.height
        );
        D2D1_RECT_F tooltipSrcRect = tooltipBackground.srcRect.ToD2DRect();

        renderTarget->DrawBitmap(tooltipBackground.bitmap, tooltipDestRect, 1.0f,
            D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, tooltipSrcRect);

        // 텍스트 렌더링
        // 이름
        renderTarget->DrawText(
            ToWString(currentHoveredItemName).c_str(),
            static_cast<UINT32>(currentHoveredItemName.length()),
            textFormat,
            D2D1::RectF(tooltipDestRect.left + 5, tooltipDestRect.top + 5, tooltipDestRect.right - 5, tooltipDestRect.bottom - 5),
            textBrush
        );

        // 설명
        renderTarget->DrawText(
            ToWString(currentHoveredItemDescription).c_str(),
            static_cast<UINT32>(currentHoveredItemDescription.length()),
            textFormat,
            D2D1::RectF(tooltipDestRect.left + 5, tooltipDestRect.top + 20, tooltipDestRect.right - 5, tooltipDestRect.bottom - 5),
            textBrush
        );

        // 개수
        std::wstring countText = L"Count: " + std::to_wstring(currentHoveredItemCount);
        renderTarget->DrawText(
            countText.c_str(),
            static_cast<UINT32>(countText.length()),
            textFormat,
            D2D1::RectF(tooltipDestRect.left + 5, tooltipDestRect.top + 40, tooltipDestRect.right - 5, tooltipDestRect.bottom - 5),
            textBrush
        );
    }

    InventorySlot* GetSlotAt(const Vec2& pos)
    {
        if (!isWindowActive || isWindowDragging) return nullptr; // 윈도우 비활성 또는 드래그 중에는 슬롯 클릭 불가

        for (auto& [key, slot] : slots)
        {
            // 슬롯의 bounds는 이미 UpdateSlotPositions에 의해 현재 창 위치에 맞게 업데이트되어 있음
            if (slot.bounds.Contains(pos))
            {
                return &slot;
            }
        }
        return nullptr;
    }

    bool IsWindowActive() const { return isWindowActive; } // 창 활성화 여부 반환

private:
    std::map<std::pair<int, int>, InventorySlot> slots;  // [region][index] -> slot
    ItemDatabase* itemDatabase;
    BitmapManager* bitmapManager;

    // UI 상태
    bool isWindowActive;
    Rect windowBounds;
    Vec2 windowPosition; // 윈도우의 현재 위치 (이동 가능)

    bool isWindowDragging;
    Vec2 dragStartMousePos;
    Vec2 dragStartWindowPos;

    // 윈도우 UI 비트맵들
    UIBitmap windowBackground;

    Rect titleBarBounds; // 타이틀바 영역
    Rect closeButtonBounds; // 닫기 버튼 영역

    UIBitmap closeButton; // 닫기 버튼의 비트맵 정보

    // 툴팁 관련
    UIBitmap tooltipBackground;
    std::string currentHoveredItemName;
    std::string currentHoveredItemDescription;
    int currentHoveredItemCount;
    Vec2 tooltipPosition;
    bool showTooltip;
};