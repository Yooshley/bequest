// Copyright Yooshley. All rights reserved.


#include "BequestGameplayTags.h"

namespace BequestGameplayTags
{
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Move, "Player.Ability.Move");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Equip, "Player.Ability.Equip");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Charge, "Player.Ability.Charge");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Attack, "Player.Ability.Attack");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Deflect, "Player.Ability.Deflect");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Guard, "Player.Ability.Guard");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Evade, "Player.Ability.Evade");
	
	UE_DEFINE_GAMEPLAY_TAG(Player_State_Guarded_Left, "Player.State.Guarded.Left");
	UE_DEFINE_GAMEPLAY_TAG(Player_State_Guarded_Right, "Player.State.Guarded.Right");
	UE_DEFINE_GAMEPLAY_TAG(Player_State_Armored, "Player.State.Armored");
	
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_Equip, "Player.Event.Equip");
	
	UE_DEFINE_GAMEPLAY_TAG(Player_Equipment_Sword_2H, "Player.Equipment.Sword.2H");
	
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_Hit, "Shared.Event.Hit");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_Hurt_Front, "Shared.Event.Hurt.Front");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_Hurt_Back, "Shared.Event.Hurt.Back");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_Hurt_Left, "Shared.Event.Hurt.Left");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_Hurt_Right, "Shared.Event.Hurt.Right");
	
	UE_DEFINE_GAMEPLAY_TAG(Shared_SetByCaller_Damage, "Shared.SetByCaller.Damage");
}