#pragma once
#include "pch.h"
#include "Inventory.h" // Inventory.h를 포함

class GameInventoryManager
{
private:
    std::unique_ptr<ItemDatabase> itemDatabase;
    std::unique_ptr<BitmapManager> bitmapManager;
    std::unique_ptr<Inventory> inventorySystem;

public:
    void Initialize(ID2D1RenderTarget* renderTarget)
    {
        // 1. 시스템 초기화
        itemDatabase = std::make_unique<ItemDatabase>();
        bitmapManager = std::make_unique<BitmapManager>(renderTarget);

        // 2. 아이템 데이터 로드
        LoadItemData();

        // 3. 아이템 비트맵 로드
        LoadItemBitmaps();

        // 4. 인벤토리 시스템 생성 (renderTarget 전달)
        inventorySystem = std::make_unique<Inventory>(itemDatabase.get(), bitmapManager.get(), renderTarget);

        // 5. 테스트 아이템 추가
        inventorySystem->AddItem(1001, 1);  // 검 1개
        inventorySystem->AddItem(2001, 15); // 포션 15개
        inventorySystem->AddItem(1002, 1);  // 방패 1개 (ARMOR 타입)
        inventorySystem->AddItem(3001, 5);  // 철광석 5개 (MATERIAL 타입)
    }

    void LoadItemData() 
    {
        itemDatabase->AddItemData(std::make_unique<ItemData>(
            1001, "강철검", "날카로운 검. 공격력 +10.", "sword_icon", 1, true, true, ItemType::ARMOR // isSynthesis, isEnforce, ItemType 추가
        ));
        itemDatabase->AddItemData(std::make_unique<ItemData>(
            1002, "나무 방패", "초보자용 방패. 방어력 +5.", "shield_icon", 1, false, true, ItemType::ARMOR
        ));
        itemDatabase->AddItemData(std::make_unique<ItemData>(
            2001, "체력포션", "체력을 50 회복합니다.", "potion_icon", 50, false, false, ItemType::CONSUMABLE // maxCount 50, isSynthesis, isEnforce, ItemType 추가
        ));
        itemDatabase->AddItemData(std::make_unique<ItemData>(
            3001, "철광석", "강철검 제작에 필요한 재료.", "ore_icon", 99, true, false, ItemType::MATERIAL
        ));
    }

    void LoadItemBitmaps()
    {
        bitmapManager->LoadBitmap("Resource/items/potion.png", "potion_icon");
        bitmapManager->LoadBitmap("Resource/items/sword.png", "sword_icon");
        bitmapManager->LoadBitmap("Resource/items/shield.png", "shield_icon");    // 새로운 아이템 비트맵
        bitmapManager->LoadBitmap("Resource/items/ore.png", "ore_icon");          // 새로운 아이템 비트맵
    }

    // 기존 SceneStandard::Render()에 추가함.
    void RenderInventory(ID2D1RenderTarget* renderTarget)
    {
        if (inventorySystem->IsWindowActive()) // 창이 활성화된 경우에만 렌더링
        {
            inventorySystem->Render(renderTarget);
        }
    }

    // 기존 입력 처리에 추가할거임. | 아직안함.
    void HandleInput(const MYHelper::Vector2F& mousePos, bool mouseDown, bool mouseUp) 
    {
        // 인벤토리 창이 활성화된 경우에만 입력 처리
        if (inventorySystem->IsWindowActive())
        {
            inventorySystem->HandleMouseMove(mousePos);
            if (mouseDown) inventorySystem->HandleMouseDown(mousePos);
            if (mouseUp) inventorySystem->HandleMouseUp(mousePos);
        }
    }

    // 테스트용 함수: 중간 영역 해금
    void UnlockMiddleInventoryRegion()
    {
        if (inventorySystem)
        {
            inventorySystem->UnlockRegion(1); // Region ID 1 (중간 4x8 영역) 해금
        }
    }

    // 테스트용 함수: 오른쪽 영역 해금
    void UnlockRightInventoryRegion()
    {
        if (inventorySystem)
        {
            inventorySystem->UnlockRegion(2); // Region ID 2 (오른쪽 4x8 영역) 해금
        }
    }
};