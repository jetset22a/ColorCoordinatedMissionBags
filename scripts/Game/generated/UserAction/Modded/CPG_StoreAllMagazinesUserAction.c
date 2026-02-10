class CPG_StoreAllMagazinesUserAction : ScriptedUserAction {
	//------------------------------------------------------------------------------------------------
	override void PerformAction(IEntity pOwnerEntity, IEntity pUserEntity)
	{		
		SCR_InventoryStorageManagerComponent userStorageManager = SCR_InventoryStorageManagerComponent.Cast(pUserEntity.FindComponent(SCR_InventoryStorageManagerComponent));
		if(!userStorageManager) {
			SCR_HintManagerComponent.GetInstance().ShowCustomHint("SCR_InventoryStorageManagerComponent not found", "TEST GROUND", 3.0);
			Print("SCR_InventoryStorageManagerComponent not found", LogLevel.NORMAL);
			return;
		}	
		
		BaseInventoryStorageComponent ownerStorageComponent = BaseInventoryStorageComponent.Cast(pOwnerEntity.FindComponent(BaseInventoryStorageComponent));
		if(!ownerStorageComponent) {
			SCR_HintManagerComponent.GetInstance().ShowCustomHint("ownerStorageComponent not found", "TEST GROUND", 3.0);
			Print("ownerStorageComponent not found", LogLevel.NORMAL);
			return;
		}
		
		array<BaseInventoryStorageComponent> storages = {};
		userStorageManager.GetStorages(storages);
		
		foreach(BaseInventoryStorageComponent storage : storages) {
			if(storage.ClassName() == "SCR_WeaponAttachmentsStorageComponent") {
				continue;
			}
			array<IEntity> items = {};
			storage.GetAll(items);
			
			foreach(IEntity item : items) {
				MagazineComponent itemMagazineComponent = MagazineComponent.Cast(item.FindComponent(MagazineComponent));
				if(itemMagazineComponent) {
					if(!userStorageManager.TryMoveItemToStorage(item, ownerStorageComponent)) {
						return;
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
			SCR_HintManagerComponent.GetInstance().ShowCustomHint("SCR_InventoryStorageManagerComponent not found", "TEST GROUND", 3.0);
			Print("SCR_InventoryStorageManagerComponent not found", LogLevel.NORMAL);
			return false;
		}
		
		array<BaseInventoryStorageComponent> storages = {};
		userStorageManager.GetStorages(storages);
		
		foreach(BaseInventoryStorageComponent storage : storages) {
			if(storage.ClassName() == "SCR_WeaponAttachmentsStorageComponent") {
				continue;
			}
			array<IEntity> items = {};
			storage.GetAll(items);
			
			foreach(IEntity item : items) {
				MagazineComponent itemMagazineComponent = MagazineComponent.Cast(item.FindComponent(MagazineComponent));
				if(itemMagazineComponent) {
					return true;
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