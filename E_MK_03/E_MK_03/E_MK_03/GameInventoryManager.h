#pragma once
#include "pch.h"
#include "Inventory.h" // Inventory.h�� ����

class GameInventoryManager
{
private:
    std::unique_ptr<ItemDatabase> itemDatabase;
    std::unique_ptr<BitmapManager> bitmapManager;
    std::unique_ptr<Inventory> inventorySystem;

public:
    void Initialize(ID2D1RenderTarget* renderTarget)
    {
        // 1. �ý��� �ʱ�ȭ
        itemDatabase = std::make_unique<ItemDatabase>();
        bitmapManager = std::make_unique<BitmapManager>(renderTarget);

        // 2. ������ ������ �ε�
        LoadItemData();

        // 3. ������ ��Ʈ�� �ε�
        LoadItemBitmaps();

        // 4. �κ��丮 �ý��� ���� (renderTarget ����)
        inventorySystem = std::make_unique<Inventory>(itemDatabase.get(), bitmapManager.get(), renderTarget);

        // 5. �׽�Ʈ ������ �߰�
        inventorySystem->AddItem(1001, 1);  // �� 1��
        inventorySystem->AddItem(2001, 15); // ���� 15��
        inventorySystem->AddItem(1002, 1);  // ���� 1�� (ARMOR Ÿ��)
        inventorySystem->AddItem(3001, 5);  // ö���� 5�� (MATERIAL Ÿ��)
    }

    void LoadItemData() 
    {
        itemDatabase->AddItemData(std::make_unique<ItemData>(
            1001, "��ö��", "��ī�ο� ��. ���ݷ� +10.", "sword_icon", 1, true, true, ItemType::ARMOR // isSynthesis, isEnforce, ItemType �߰�
        ));
        itemDatabase->AddItemData(std::make_unique<ItemData>(
            1002, "���� ����", "�ʺ��ڿ� ����. ���� +5.", "shield_icon", 1, false, true, ItemType::ARMOR
        ));
        itemDatabase->AddItemData(std::make_unique<ItemData>(
            2001, "ü������", "ü���� 50 ȸ���մϴ�.", "potion_icon", 50, false, false, ItemType::CONSUMABLE // maxCount 50, isSynthesis, isEnforce, ItemType �߰�
        ));
        itemDatabase->AddItemData(std::make_unique<ItemData>(
            3001, "ö����", "��ö�� ���ۿ� �ʿ��� ���.", "ore_icon", 99, true, false, ItemType::MATERIAL
        ));
    }

    void LoadItemBitmaps()
    {
        bitmapManager->LoadBitmap("Resource/items/potion.png", "potion_icon");
        bitmapManager->LoadBitmap("Resource/items/sword.png", "sword_icon");
        bitmapManager->LoadBitmap("Resource/items/shield.png", "shield_icon");    // ���ο� ������ ��Ʈ��
        bitmapManager->LoadBitmap("Resource/items/ore.png", "ore_icon");          // ���ο� ������ ��Ʈ��
    }

    // ���� SceneStandard::Render()�� �߰���.
    void RenderInventory(ID2D1RenderTarget* renderTarget)
    {
        if (inventorySystem->IsWindowActive()) // â�� Ȱ��ȭ�� ��쿡�� ������
        {
            inventorySystem->Render(renderTarget);
        }
    }

    // ���� �Է� ó���� �߰��Ұ���. | ��������.
    void HandleInput(const MYHelper::Vector2F& mousePos, bool mouseDown, bool mouseUp) 
    {
        // �κ��丮 â�� Ȱ��ȭ�� ��쿡�� �Է� ó��
        if (inventorySystem->IsWindowActive())
        {
            inventorySystem->HandleMouseMove(mousePos);
            if (mouseDown) inventorySystem->HandleMouseDown(mousePos);
            if (mouseUp) inventorySystem->HandleMouseUp(mousePos);
        }
    }

    // �׽�Ʈ�� �Լ�: �߰� ���� �ر�
    void UnlockMiddleInventoryRegion()
    {
        if (inventorySystem)
        {
            inventorySystem->UnlockRegion(1); // Region ID 1 (�߰� 4x8 ����) �ر�
        }
    }

    // �׽�Ʈ�� �Լ�: ������ ���� �ر�
    void UnlockRightInventoryRegion()
    {
        if (inventorySystem)
        {
            inventorySystem->UnlockRegion(2); // Region ID 2 (������ 4x8 ����) �ر�
        }
    }
};