class CPG_BaseStoreAllUserAction : ScriptedUserAction {
	array<string> GetProtectedStorageNames() {
		return {};
	}
	
	array<ECommonItemType> GetItemTypesToStore() {
		return {};
	}
	
	//------------------------------------------------------------------------------------------------
	override void PerformAction(IEntity pOwnerEntity, IEntity pUserEntity)
	{		
		SCR_InventoryStorageManagerComponent userStorageManager = SCR_InventoryStorageManagerComponent.Cast(pUserEntity.FindComponent(SCR_InventoryStorageManagerComponent));
		if(!userStorageManager) {
			Print("SCR_InventoryStorageManagerComponent not found", LogLevel.NORMAL);
			return;
		}	
		
		BaseInventoryStorageComponent ownerStorageComponent = BaseInventoryStorageComponent.Cast(pOwnerEntity.FindComponent(BaseInventoryStorageComponent));
		if(!ownerStorageComponent) {
			Print("ownerStorageComponent not found", LogLevel.NORMAL);
			return;
		}
		
		array<BaseInventoryStorageComponent> storages = {};
		userStorageManager.GetStorages(storages);
		
		foreach(BaseInventoryStorageComponent storage : storages) {
			if(GetProtectedStorageNames().Contains(storage.ClassName())) {
				continue;
			}
			array<IEntity> items = {};
			storage.GetAll(items);
			
			foreach(IEntity item : items) {
				InventoryItemComponent inventoryItemComponent = InventoryItemComponent.Cast(item.FindComponent(InventoryItemComponent));
				if(inventoryItemComponent && inventoryItemComponent.GetAttributes()) {
					ECommonItemType itemType = inventoryItemComponent.GetAttributes().GetCommonType();
					if(GetItemTypesToStore().Contains(itemType)) {
						if(!userStorageManager.TryMoveItemToStorage(item, ownerStorageComponent)) {
							return;
						}
					}
				}
			}
		}
	}

	//------------------------------------------------------------------------------------------------
	override bool CanBeShownScript(IEntity user)
	{
		SCR_InventoryStorageManagerComponent userStorageManager = SCR_InventoryStorageManagerComponent.Cast(user.FindComponent(SCR_InventoryStorageManagerComponent));
		if(!userStorageManager) {
			Print("SCR_InventoryStorageManagerComponent not found", LogLevel.NORMAL);
			return false;
		}
		
		array<BaseInventoryStorageComponent> storages = {};
		userStorageManager.GetStorages(storages);
		
		foreach(BaseInventoryStorageComponent storage : storages) {
			array<IEntity> items = {};
			storage.GetAll(items);
			
			foreach(IEntity item : items) {
				InventoryItemComponent inventoryItemComponent = InventoryItemComponent.Cast(item.FindComponent(InventoryItemComponent));
				if(inventoryItemComponent && inventoryItemComponent.GetAttributes()) {
					ECommonItemType itemType = inventoryItemComponent.GetAttributes().GetCommonType();
					if(GetItemTypesToStore().Contains(itemType)) {
						return true;
					}
				}
			}
		}
		
		return false;
	}

	//------------------------------------------------------------------------------------------------
	override bool CanBePerformedScript(IEntity user)
	{
		return true;
	}

	//------------------------------------------------------------------------------------------------
	override bool HasLocalEffectOnlyScript()
	{
		return false;
	}
}