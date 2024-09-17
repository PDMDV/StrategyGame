
#include "Widgets/GS_ActionButton.h"
#include "Action/GS_ActionDataAsset.h"

UGS_ActionInfo* UGS_ActionButton::GetAction()
{
	return ActionAsset->Action;
}
