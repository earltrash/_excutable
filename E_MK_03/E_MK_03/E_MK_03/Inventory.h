#pragma once
#include "pch.h"
#include "Object.h"
#include "BitmapManager.h"
#include "UIUtility.h"
#include "Renderer.h"

enum class ItemType
{
    ARMOR,       // ��
    CONSUMABLE,  // �Ҹ�ǰ
    MATERIAL     // ���
};

struct  ItemData
{
    int itemId;                                       // ������ ���� Ű
    std::string name;                                 // �̸�
    std::string description;                          // ����
    std::string iconTexture;                          // �ؽ�ó Ű
    int maxCount;                                     // �ִ� ����(���� 1)
    bool isSynthesis;                                 // �ռ� ���� ����
    bool isEnforce;                                   // ��ȭ ���� ����
    std::unordered_map<std::string, float> stats;     // �ɷ�ġ (���ݷ�, ���� ��)
    std::vector<std::string> effects;                 // Ư�� ȿ����
    ItemType type;

    ItemData(int id, const std::string& name, const std::string& desc,
        const std::string& icon, int stack = 1, bool synthesis = false, bool enforce = false, ItemType itemType = ItemType::MATERIAL) // isSynthesis, isEnforce �⺻�� �߰�
        : itemId(id), name(name), description(desc), iconTexture(icon),
        maxCount(stack), isSynthesis(synthesis), isEnforce(enforce), type(itemType) {}

    // ���� �������� Ȯ��
    bool IsStackable() const
    {
        return maxCount > 1;
    }

    // ��� ���������� Ȯ��
    bool IsEquipment() const
    {
        return type == ItemType::ARMOR;
    }

    // �Ҹ�ǰ���� Ȯ��
    bool IsConsumable() const
    {
        return type == ItemType::CONSUMABLE;
    }

    // ��������� Ȯ�� (�ߺ��� IsConsumable()�� IsMaterial()�� ����)
    bool IsMaterial() const
    {
        return type == ItemType::MATERIAL;
    }

    // �ɷ�ġ �߰�/����
    void SetStat(const std::string& statName, float value)
    {
        stats[statName] = value;
    }

    // �ɷ�ġ ��ȸ
    float GetStat(const std::string& statName) const
    {
        auto it = stats.find(statName);
        return it != stats.end() ? it->second : 0.0f;
    }

    // Ư�� ȿ�� �߰�
    void AddEffect(const std::string& effect)
    {
        effects.push_back(effect);
    }

    // ������
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

// ������ �ν��Ͻ�
struct ItemInstance
{
    int itemId;
    int count;

    ItemInstance(int id = 0, int cnt = 0) : itemId(id), count(cnt) {}
    bool IsEmpty() const { return itemId == 0 || count == 0; }
};

// ������ �����ͺ��̽�
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

// Direct2D ������ ������ ���� UI ��������Ʈ
struct UIBitmap
{
    ID2D1Bitmap* bitmap;           // Direct2D ��Ʈ��
    Rect srcRect;                  // �ҽ� ���� (��������Ʈ ��Ʈ��)
    Vec2 position;                 // ������ ��ġ
    Vec2 size;                     // ������ ũ��
    float opacity;                 // ����

    UIBitmap() : bitmap(nullptr), opacity(1.0f) {}
};

class InventorySlot
{
public:
    ItemInstance item;             // ���� ������ ������ (ID, ����)
    bool isEnabled;

    UIBitmap backgroundBitmap;     // ���� ��� ��Ʈ��
    UIBitmap itemBitmap;           // ������ ������ ��Ʈ��
    UIBitmap overlayBitmap;        // ȣ��/���� ȿ�� ��Ʈ��

    // UI��
    Rect bounds;
    bool isHovered;
    bool isSelected;

    InventorySlot() : isEnabled(true), isHovered(false), isSelected(false) {}

    void SetBounds(const Rect& rect)
    {
        bounds = rect;

        // ��� ��Ʈ�� ����
        backgroundBitmap.position = Vec2(rect.x, rect.y);
        backgroundBitmap.size = Vec2(rect.width, rect.height);

        // ������ ��Ʈ�� ���� (�е� ����)
        float padding = 4.0f;
        itemBitmap.position = Vec2(rect.x + padding, rect.y + padding);
        itemBitmap.size = Vec2(rect.width - padding * 2, rect.height - padding * 2);

        // �������� ����
        overlayBitmap.position = Vec2(rect.x, rect.y);
        overlayBitmap.size = Vec2(rect.width, rect.height);
    }

    // === �ٽ� ���� �Լ� ===
    void UpdateItemBitmap(BitmapManager* bitmapManager, const ItemDatabase* itemDB)
    {
        if (!item.IsEmpty()) 
        {
            // 1. ������ ������ ��ȸ
            const ItemData* data = itemDB->GetItemData(item.itemId);
            if (data)
            {
                // 2. ��Ʈ�� ���� (������ ������)
                itemBitmap.bitmap = bitmapManager->GetBitmap(data->iconTexture);
                itemBitmap.srcRect = Rect(0, 0, 48, 48);  // ��ü ������ ��� (������. ���� �̹��� ����� ���� ����.)
                itemBitmap.opacity = 1.0f;
            }
            else
            {
                itemBitmap.bitmap = nullptr; // ������ �����Ͱ� ������ ��Ʈ���� ���
            }
        }
        else
        {
            // �� ������ ��� empty_slot_item ��Ʈ���� ���
            itemBitmap.bitmap = bitmapManager->GetBitmap("slot_normal"); // �� ���Կ� �̹��� Ű
            itemBitmap.srcRect = Rect(0, 0, 48, 48); // �⺻ ũ��
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

        std::cout << "���� ��� Ű: " << bgKey << std::endl;

        backgroundBitmap.bitmap = bitmapManager->GetBitmap(bgKey);
        backgroundBitmap.srcRect = Rect(0, 0, 48, 48);  // ���� ũ�� (����)
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
        InitializeWindowBounds();     // ������ �ٿ�� �ʱ�ȭ (regions���� ����)
        InitializeRegions();          // ���� �ʱ�ȭ
        LoadUIBitmaps();              // �̹��� �ε��ؼ� ��������
        InitializeSlots();            // ���� �ʱ�ȭ
        InitializeTextRendering();    // �ؽ�Ʈ ������ �ʱ�ȭ

        dragState.isDragging = false; // �巡�� ���� �ʱ�ȭ
    }

    ~Inventory() // �Ҹ��ڿ��� DirectWrite �ڿ� ����
    {
        SafeRelease(&textFormat);
        SafeRelease(&textBrush);
    }

    // �κ��丮 ����
    struct Region
    {
        int id;
        bool isEnabled;
        Rect bounds;
        Vec2 gridSize;  // 4x8
    };
    std::vector<Region> regions;

    // �巡�� ����
    struct DragState
    {
        bool isDragging;
        InventorySlot* sourceSlot;
        ItemInstance draggedItem;
        Vec2 mousePos;
        UIBitmap dragBitmap;  // �巡�� ���� ������ ��Ʈ��
    } dragState;

    // �ؽ�Ʈ �������� ���� DWrite ��ü (����)
    IDWriteTextFormat* textFormat;
    ID2D1SolidColorBrush* textBrush;
    ID2D1RenderTarget* renderTarget; // �ؽ�Ʈ �귯�� ������

    void InitializeWindowBounds()
    {
        float slotSize = 48.0f;
        float padding = 4.0f;
        float totalSlotDimension = slotSize + padding + 3.0f;  // �߰� ���� ���

        // ��ü ������ ũ�� ��� (12x8 �׸��带 ��� ���� + ���� + Ÿ��Ʋ�� ����)
        float totalGridWidth = 12 * totalSlotDimension;
        float totalGridHeight = 8 * totalSlotDimension;

        // �ʱ� ������ ��ġ �� ũ�� ����
        windowBounds = Rect(
            20.0f, // ���� ����
            50.0f, // ��� ���� (Ÿ��Ʋ�� ����)
            totalGridWidth + 40.0f, // �¿� ���� �ջ� (20 + totalGridWidth + 20)
            totalGridHeight + 60.0f // ���� ���� �ջ� (50 + totalGridHeight + 10)
        );
        windowPosition = Vec2(windowBounds.x, windowBounds.y); // �ʱ� ��ġ ����

        // Ÿ��Ʋ�� ���� ���� (â ��ġ�� �����)
        titleBarBounds = Rect(windowPosition.x, windowPosition.y, windowBounds.width, 30.0f);

        // �ݱ� ��ư ���� ���� (������ ���, â ��ġ�� �����)
        float closeButtonSize = 22.0f;
        closeButtonBounds = Rect(
            windowPosition.x + windowBounds.width - closeButtonSize - 5,
            windowPosition.y + 5,
            closeButtonSize,
            closeButtonSize
        );

        // ������ ��� ��Ʈ���� ������ ��ġ/ũ�� ����
        windowBackground.position = windowPosition;
        windowBackground.size = Vec2(windowBounds.width, windowBounds.height);
        windowBackground.srcRect = Rect(0, 0, windowBounds.width, windowBounds.height); // ���� �̹��� ũ��

        // �ݱ� ��ư ��Ʈ���� ������ ��ġ/ũ�� ����
        closeButton.position = Vec2(closeButtonBounds.x, closeButtonBounds.y);
        closeButton.size = Vec2(closeButtonBounds.width, closeButtonBounds.height);
        closeButton.srcRect = Rect(0, 0, 27, 27); // �ݱ� ��ư �̹��� ũ��
    }

    void InitializeRegions()
    {
        regions.resize(3); // 3���� ���� (4x8, 4x8, 4x8)

        float slotSize = 48.0f;
        float padding = 4.0f;
        float totalSlotDimension = slotSize + padding;

        // windowBounds�� ���� ������ �������� ��ġ
        float currentRegionX = windowPosition.x + 23.0f; // ������ ���� ����

        // Region 0: �⺻ �ر� ���� (4x8)
        regions[0].id = 0;
        regions[0].isEnabled = true;
        regions[0].gridSize = Vec2(4, 8);
        regions[0].bounds = Rect(
            currentRegionX,
            windowPosition.y + 50.0f, // ������ ��� ���� + Ÿ��Ʋ�� ����
            regions[0].gridSize.x * totalSlotDimension,
            regions[0].gridSize.y * totalSlotDimension
        );
        currentRegionX += regions[0].bounds.width + 23.0f; // ���� ���� ���� X

        // Region 1: �߰� ��� ���� (4x8)
        regions[1].id = 1;
        regions[1].isEnabled = false; // ���
        regions[1].gridSize = Vec2(4, 8);
        regions[1].bounds = Rect(
            currentRegionX,
            windowPosition.y + 50.0f,
            regions[1].gridSize.x * totalSlotDimension,
            regions[1].gridSize.y * totalSlotDimension
        );
        currentRegionX += regions[1].bounds.width + 15.0f;

        // Region 2: ������ ��� ���� (4x8)
        regions[2].id = 2;
        regions[2].isEnabled = false; // ���
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

                    // ���� ��ġ�� �ش� Region�� bounds�� �������� ���
                    float slotX = region.bounds.x + x * totalSlotDimension;
                    float slotY = region.bounds.y + y * totalSlotDimension;

                    slot.SetBounds(Rect(slotX, slotY, slotSize, slotSize));
                    slot.isEnabled = region.isEnabled; // ������ Ȱ��ȭ ���¿� ���� ���� Ȱ��ȭ ����
                    slot.UpdateBackgroundBitmap(bitmapManager); // �ʱ� ��� ����
                }
            }
        }
    }

    void LoadUIBitmaps()
    {
        // UI ��Ʈ�ʵ� �ε� �̹��� �� �������� 
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

        std::cout << "slot_normal: " << (slotNormal ? "�ε� ����" : "�ε� ����") << std::endl;
        std::cout << "window_bg: " << (windowBg ? "�ε� ����" : "�ε� ����") << std::endl;
        std::cout << "close_button: " << (closeBtn ? "�ε� ����" : "�ε� ����") << std::endl;

        windowBackground.bitmap = bitmapManager->GetBitmap("window_bg");
        closeButton.bitmap = bitmapManager->GetBitmap("close_button");
        tooltipBackground.bitmap = bitmapManager->GetBitmap("tooltip_background");
        tooltipBackground.srcRect = Rect(0, 0, 100, 60); // ������. ���� ��� ũ��

        std::cout << "=== ��Ʈ�� �ε� �Ϸ� ===" << std::endl;
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

    // ������ �߰� (������ + UI �ڵ� ����)
    bool AddItem(int itemId, int count = 1)
    {
        const ItemData* itemData = itemDatabase->GetItemData(itemId);
        if (!itemData) return false;

        // �� ���� ã��
        for (auto& [key, slot] : slots)
        {
            if (!slot.isEnabled) continue; // ��Ȱ��ȭ�� ���Կ��� �߰� �Ұ�

            // ���� ������ �������̶�� ���� ���Կ� ��ġ�� �õ� (����)
            if (itemData->IsStackable() && slot.item.itemId == itemId && (slot.item.count + count) <= itemData->maxCount)
            {
                slot.item.count += count;
                slot.UpdateItemBitmap(bitmapManager, itemDatabase); // ���� ������ ��Ʈ�� ������ ������, Ȥ�� �� ��� ȣ��
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

    // ���� �ر� �Լ�
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

    // ���콺 �̺�Ʈ ó��
    void HandleMouseMove(const Vec2& mousePos)
    {
        if (!isWindowActive)
        {
            showTooltip = false;
            return;
        }

        // ������ �巡�� ���� ��
        if (isWindowDragging)
        {
            float deltaX = mousePos.x - dragStartMousePos.x;
            float deltaY = mousePos.y - dragStartMousePos.y;
            windowPosition = Vec2(dragStartWindowPos.x + deltaX, dragStartWindowPos.y + deltaY);

            // ������ �ٿ��, Ÿ��Ʋ��, �ݱ� ��ư �ٿ�� ������Ʈ
            windowBounds.x = windowPosition.x;
            windowBounds.y = windowPosition.y;
            titleBarBounds.x = windowPosition.x;
            titleBarBounds.y = windowPosition.y;
            closeButtonBounds.x = windowPosition.x + windowBounds.width - closeButtonBounds.width - 5;
            closeButtonBounds.y = windowPosition.y + 5;

            // ���Ե��� ��ġ�� ������Ʈ�ؾ� ��
            UpdateSlotPositions();
        }
        else // ������ �巡�� ���� �ƴ� ���� ���� ȣ�� �� ���� ó��
        {
            showTooltip = false;
            InventorySlot* hoveredSlot = nullptr;

            // ���� ȣ�� ���� ������Ʈ
            for (auto& [key, slot] : slots)
            {
                bool wasHovered = slot.isHovered;
                // ������ ���� ������ ��ġ(�̵��� â�� ���� �޶���)�� �������� Contains üũ
                // slot.bounds�� �̹� UpdateSlotPositions�� ���� ���� â ��ġ�� �°� ������Ʈ�� (Ȥ�� �̹� �ʱ�ȭ �� �ùٸ��� ������)
                slot.isHovered = slot.bounds.Contains(mousePos);

                if (wasHovered != slot.isHovered)
                {
                    slot.UpdateBackgroundBitmap(bitmapManager);
                }

                if (slot.isHovered && !slot.IsEmpty())
                {
                    hoveredSlot = &slot; // ���� ���콺�� �ö� ����
                }
            }

            // ���� ���� ������Ʈ
            if (hoveredSlot)
            {
                const ItemData* data = itemDatabase->GetItemData(hoveredSlot->item.itemId);
                if (data)
                {
                    currentHoveredItemName = data->name;
                    currentHoveredItemDescription = data->description;
                    currentHoveredItemCount = hoveredSlot->item.count;
                    // ���� ��ġ�� ���콺 Ŀ�� ������ ���� (â�� �̵��ص� ��������� ����)
                    tooltipPosition = Vec2(mousePos.x + 15, mousePos.y + 15);
                    showTooltip = true;
                }
            }
        }

        // ������ �巡�� ���� �� (���콺 ��ġ ������Ʈ)
        if (dragState.isDragging)
        {
            dragState.mousePos = mousePos;
        }
    }
    
    void HandleMouseDown(const Vec2& mousePos)
    {
        if (!isWindowActive) return;

        // �ݱ� ��ư Ŭ�� ó��
        if (closeButtonBounds.Contains(mousePos))
        {
            isWindowActive = false; // â ��Ȱ��ȭ
            showTooltip = false; // ���� ����
            return;
        }

        // Ÿ��Ʋ�� �巡�� ����
        if (titleBarBounds.Contains(mousePos))
        {
            isWindowDragging = true;
            dragStartMousePos = mousePos;
            dragStartWindowPos = windowPosition;
            return; // Ÿ��Ʋ�� �巡�� ���� �� �ٸ� Ŭ�� �̺�Ʈ�� ����
        }

        // ���� �巡�� ���� (���� ����)
        InventorySlot* slot = GetSlotAt(mousePos); // ���� â ��ġ�� ����Ͽ� ���� ��������
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

        // ������ �巡�� ����
        if (isWindowDragging)
        {
            isWindowDragging = false;
            return;
        }

        // ������ �巡�� ����
        if (!dragState.isDragging) return;

        bool placed = false;
        InventorySlot* targetSlot = GetSlotAt(mousePos); // ���� ���콺 ��ġ�� ������ �ٽ� ã��

        if (targetSlot && targetSlot->isEnabled)
        {
            // ���� ������ �������̶�� ��ġ�� �õ�
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
                // �� ���Կ� ���
                targetSlot->item = dragState.draggedItem;
                targetSlot->UpdateItemBitmap(bitmapManager, itemDatabase);
                placed = true;
            }
            else
            {
                // �ٸ� �������� �ִ� ���Կ� ��� (��ȯ ���� �߰� ����)
                // ����� �׳� ���� ��ġ�� �ǵ���
            }
        }

        // ��ġ ���н� ���� ��ġ�� ����
        if (!placed)
        {
            dragState.sourceSlot->item = dragState.draggedItem;
            dragState.sourceSlot->UpdateItemBitmap(bitmapManager, itemDatabase);
        }

        dragState.isDragging = false;
    }

    // â�� �̵��� �� ���Ե��� ���� ������ ��ġ�� ������Ʈ�մϴ�.
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

                        // ���� ��ġ�� �ش� Region�� bounds�� �������� ��� (regions.bounds�� InitializeRegions���� windowPosition�� ���� �̹� ������)
                        float slotX = region.bounds.x + x * totalSlotDimension;
                        float slotY = region.bounds.y + y * totalSlotDimension;

                        slot.SetBounds(Rect(slotX, slotY, slotSize, slotSize));
                    }
                }
            }
        }
    }

    // === ���� ������ ��Ŀ� ���� ������ �Լ� ===
    void Render(ID2D1RenderTarget* renderTarget)
    {
        if (!isWindowActive) return;

        // 1. ������ ��� ������
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

        // 2. Ÿ��Ʋ�� �� �ݱ� ��ư ������
        RenderTitleBar(renderTarget);
        RenderCloseButton(renderTarget);

        // 3. ��� ���� ������
        for (const auto& [key, slot] : slots)
        {
            RenderSlot(renderTarget, slot);
        }

        // 4. �巡�� ���� ������ ������
        if (dragState.isDragging && dragState.dragBitmap.bitmap)
        {
            D2D1_RECT_F dragDestRect = D2D1::RectF(
                dragState.mousePos.x - dragState.dragBitmap.size.x / 2.0f, // ���콺 �߾ӿ� ������
                dragState.mousePos.y - dragState.dragBitmap.size.y / 2.0f,
                dragState.mousePos.x + dragState.dragBitmap.size.x / 2.0f,
                dragState.mousePos.y + dragState.dragBitmap.size.y / 2.0f
            );
            renderTarget->DrawBitmap(dragState.dragBitmap.bitmap, dragDestRect, 0.8f);
        }

        // 5. ���� ������ (���� �������� �������Ͽ� �ٸ� UI ���� ǥ��)
        if (showTooltip)
        {
            RenderTooltip(renderTarget);
        }
    }

    void RenderSlot(ID2D1RenderTarget* renderTarget, const InventorySlot& slot)
    {
        std::cout << "=== RenderSlot ȣ�� ===" << std::endl;
        std::cout << "slot.isEnabled: " << (slot.isEnabled ? "true" : "false") << std::endl;
        std::cout << "slot.backgroundBitmap.bitmap: " << (slot.backgroundBitmap.bitmap ? "����" : "nullptr") << std::endl;

        // 1. ���� ��� ������ (������ bounds�� �̹� UpdateSlotPositions�� ���� ���� â ��ġ�� �°� ������Ʈ��)
        if (slot.backgroundBitmap.bitmap)
        {
            std::cout << "��� ��Ʈ�� ������ �õ�" << std::endl;

            D2D1_RECT_F destRect = slot.bounds.ToD2DRect();
            D2D1_RECT_F srcRect = slot.backgroundBitmap.srcRect.ToD2DRect();
            renderTarget->DrawBitmap(slot.backgroundBitmap.bitmap, destRect,
                slot.backgroundBitmap.opacity,
                D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, srcRect);

            std::cout << "��� ��Ʈ�� ������ �Ϸ�" << std::endl;
        }

        // ��Ȱ��ȭ�� ������ ��slot�̹��� �׸�.
        if (!slot.isEnabled)
        {
            std::cout << "��Ȱ��ȭ�� �����̹Ƿ� ��游 �������ϰ� ����" << std::endl;
            return;
        }

        // 2. ������ ������ ������
        if (!slot.IsEmpty() && slot.itemBitmap.bitmap)
        {
            D2D1_RECT_F itemDestRect = D2D1::RectF(
                slot.itemBitmap.position.x, // itemBitmap.position�� SetBounds���� �̹� ���� bounds�� ���� ������
                slot.itemBitmap.position.y,
                slot.itemBitmap.position.x + slot.itemBitmap.size.x,
                slot.itemBitmap.position.y + slot.itemBitmap.size.y
            );
            D2D1_RECT_F itemSrcRect = slot.itemBitmap.srcRect.ToD2DRect();

            renderTarget->DrawBitmap(slot.itemBitmap.bitmap, itemDestRect,
                slot.itemBitmap.opacity,
                D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, itemSrcRect);

            // 3. ������ ���� �ؽ�Ʈ
            if (slot.item.count > 1 && textFormat && textBrush)
            {
                std::wstring countText = std::to_wstring(slot.item.count);
                // �ؽ�Ʈ ��ġ�� ���� ���� �ϴܿ� ��ġ (����)
                D2D1_RECT_F textRect = D2D1::RectF(
                    slot.bounds.x + slot.bounds.width - 30, // ���� ����
                    slot.bounds.y + slot.bounds.height - 20, // �ϴ� ����
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
            // Ÿ��Ʋ�� ������ windowPosition�� ���� �̹� ������Ʈ��
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
            // �ݱ� ��ư ��ġ�� closeButtonBounds�� �̹� ������Ʈ��
            D2D1_RECT_F destRect = closeButtonBounds.ToD2DRect();
            D2D1_RECT_F srcRect = closeButton.srcRect.ToD2DRect();
            renderTarget->DrawBitmap(closeButton.bitmap, destRect, closeButton.opacity,
                D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, srcRect);
        }
    }

    void RenderTooltip(ID2D1RenderTarget* renderTarget)
    {
        if (!tooltipBackground.bitmap || !textFormat || !textBrush) return;

        // ���� ��� ������
        D2D1_RECT_F tooltipDestRect = D2D1::RectF(
            tooltipPosition.x,
            tooltipPosition.y,
            tooltipPosition.x + tooltipBackground.srcRect.width,
            tooltipPosition.y + tooltipBackground.srcRect.height
        );
        D2D1_RECT_F tooltipSrcRect = tooltipBackground.srcRect.ToD2DRect();

        renderTarget->DrawBitmap(tooltipBackground.bitmap, tooltipDestRect, 1.0f,
            D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, tooltipSrcRect);

        // �ؽ�Ʈ ������
        // �̸�
        renderTarget->DrawText(
            ToWString(currentHoveredItemName).c_str(),
            static_cast<UINT32>(currentHoveredItemName.length()),
            textFormat,
            D2D1::RectF(tooltipDestRect.left + 5, tooltipDestRect.top + 5, tooltipDestRect.right - 5, tooltipDestRect.bottom - 5),
            textBrush
        );

        // ����
        renderTarget->DrawText(
            ToWString(currentHoveredItemDescription).c_str(),
            static_cast<UINT32>(currentHoveredItemDescription.length()),
            textFormat,
            D2D1::RectF(tooltipDestRect.left + 5, tooltipDestRect.top + 20, tooltipDestRect.right - 5, tooltipDestRect.bottom - 5),
            textBrush
        );

        // ����
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
        if (!isWindowActive || isWindowDragging) return nullptr; // ������ ��Ȱ�� �Ǵ� �巡�� �߿��� ���� Ŭ�� �Ұ�

        for (auto& [key, slot] : slots)
        {
            // ������ bounds�� �̹� UpdateSlotPositions�� ���� ���� â ��ġ�� �°� ������Ʈ�Ǿ� ����
            if (slot.bounds.Contains(pos))
            {
                return &slot;
            }
        }
        return nullptr;
    }

    bool IsWindowActive() const { return isWindowActive; } // â Ȱ��ȭ ���� ��ȯ

private:
    std::map<std::pair<int, int>, InventorySlot> slots;  // [region][index] -> slot
    ItemDatabase* itemDatabase;
    BitmapManager* bitmapManager;

    // UI ����
    bool isWindowActive;
    Rect windowBounds;
    Vec2 windowPosition; // �������� ���� ��ġ (�̵� ����)

    bool isWindowDragging;
    Vec2 dragStartMousePos;
    Vec2 dragStartWindowPos;

    // ������ UI ��Ʈ�ʵ�
    UIBitmap windowBackground;

    Rect titleBarBounds; // Ÿ��Ʋ�� ����
    Rect closeButtonBounds; // �ݱ� ��ư ����

    UIBitmap closeButton; // �ݱ� ��ư�� ��Ʈ�� ����

    // ���� ����
    UIBitmap tooltipBackground;
    std::string currentHoveredItemName;
    std::string currentHoveredItemDescription;
    int currentHoveredItemCount;
    Vec2 tooltipPosition;
    bool showTooltip;
};