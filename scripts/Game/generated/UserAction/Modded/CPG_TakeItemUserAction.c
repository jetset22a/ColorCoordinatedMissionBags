class CPG_TakeItemUserAction : ScriptedUserAction {
	int m_UserNumOfItems;
	
	InventorySearchPredicate GetSearchPredicate(IEntity pOwnerEntity) {
		return null;
	}
	
	string GetItemName() {
		return "";
	}
	
	//------------------------------------------------------------------------------------------------
	override void PerformAction(IEntity pOwnerEntity, IEntity pUserEntity)
	{		
		SCR_InventoryStorageManagerComponent userStorageManager = SCR_InventoryStorageManagerComponent.Cast(pUserEntity.FindComponent(SCR_InventoryStorageManagerComponent));
		if(!userStorageManager) {
			Print("SCR_InventoryStorageManagerComponent not found", LogLevel.NORMAL);
			return;
		}
		
		SCR_CharacterControllerComponent characterControllerComponent = SCR_CharacterControllerComponent.Cast(pUserEntity.FindComponent(SCR_CharacterControllerComponent));
		if(!characterControllerComponent) {
			Print("characterControllerComponent not found", LogLevel.NORMAL);
			return;
		}
		
		SCR_InventoryStorageManagerComponent ownerStorageManager = SCR_InventoryStorageManagerComponent.Cast(pOwnerEntity.FindComponent(SCR_InventoryStorageManagerComponent));
		if(!ownerStorageManager) {
			Print("ownerStorageManager not found", LogLevel.NORMAL);
			return;
		}
		
		IEntity item = ownerStorageManager.FindItem(GetSearchPredicate(pOwnerEntity));
		if(!item) {
			Print("item not found", LogLevel.NORMAL);
			return;
		}
		
		BaseInventoryStorageComponent storage = userStorageManager.FindStorageForItem(item);
		if(storage && ownerStorageManager.TryMoveItemToStorage(item, storage)) {
			characterControllerComponent.TryPlayItemGesture(EItemGesture.EItemGesturePickUp);
		}
		
	}

	//------------------------------------------------------------------------------------------------
	override bool CanBeShownScript(IEntity user)
	{	
		m_UserNumOfItems = 0;
		SCR_InventoryStorageManagerComponent userStorageManager = SCR_InventoryStorageManagerComponent.Cast(user.FindComponent(SCR_InventoryStorageManagerComponent));
		if(!userStorageManager) {
			Print("SCR_InventoryStorageManagerComponent not found", LogLevel.NORMAL);
		}
		
		m_UserNumOfItems = userStorageManager.CountItem(GetSearchPredicate(null));
		
		return true;
	}
	
	override bool GetActionNameScript(out string outName) {
		if(!m_UserNumOfItems) {
			m_UserNumOfItems = 0;
		}
		
		outName = "Take " + GetItemName() + " (" + m_UserNumOfItems.ToString() + ")";
		
		return true;
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