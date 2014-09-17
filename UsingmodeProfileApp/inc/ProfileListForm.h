//
// Copyright (c) 2012 Samsung Electronics Co., Ltd.
//
// Licensed under the Flora License, Version 1.1 (the License);
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://floralicense.org/license/
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an AS IS BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

#ifndef _PROFILE_LIST_FORM_H_
#define _PROFILE_LIST_FORM_H_

#include <FBase.h>
//#include <FSocial.h>
#include <FUi.h>
#include <FIo.h>

class ProfileListForm
	: public Tizen::Ui::Controls::Form
	, public Tizen::Ui::IActionEventListener
//	, public Tizen::Social::ICalendarbookEventListener
	, public Tizen::Ui::Controls::IFormBackEventListener
	, public Tizen::Ui::Controls::IListViewItemEventListener
	, public Tizen::Ui::Controls::IListViewItemProvider
	, public Tizen::Ui::Scenes::ISceneEventListener
{

public:
	ProfileListForm();
	virtual ~ProfileListForm();

	bool Initialize(void);
	void SaveUsingmodeProfile(Tizen::Base::String title, 		int year,
			int month,
			int day,
			int hour,
			int minute,
			int year2,
			int month2,
			int day2,
			int hour2,
			int minute2,
			int latitude,
			int longitude,
			int volume,
			int wifi,
			Tizen::Base::String memo);
public:
	virtual result OnInitializing(void);
	virtual result OnTerminating(void);
	virtual void OnActionPerformed(const Tizen::Ui::Control& source, int actionId);

	virtual void OnFormBackRequested(Tizen::Ui::Controls::Form& source);

	virtual void OnListViewItemStateChanged(Tizen::Ui::Controls::ListView& listView, int index, int elementId, Tizen::Ui::Controls::ListItemStatus status);
	virtual void OnListViewItemSwept(Tizen::Ui::Controls::ListView& listView, int index, Tizen::Ui::Controls::SweepDirection direction);
	virtual void OnListViewContextItemStateChanged(Tizen::Ui::Controls::ListView& listView, int index, int elementId, Tizen::Ui::Controls::ListContextItemStatus state);
	virtual void OnItemReordered(Tizen::Ui::Controls::ListView& view, int oldIndex, int newIndex);
	virtual int GetItemCount(void);
	virtual Tizen::Ui::Controls::ListItemBase* CreateItem(int index, int itemWidth);
	virtual bool DeleteItem(int index, Tizen::Ui::Controls::ListItemBase* pItem, int itemWidth);

	virtual void OnSceneActivatedN(const Tizen::Ui::Scenes::SceneId& previousSceneId, const Tizen::Ui::Scenes::SceneId& currentSceneId, Tizen::Base::Collection::IList* pArgs);
	virtual void OnSceneDeactivated(const Tizen::Ui::Scenes::SceneId& currentSceneId, const Tizen::Ui::Scenes::SceneId& nextSceneId);

	virtual void OnCalendarEventsChanged(const Tizen::Base::Collection::IList& eventChangeInfoList){}
	virtual void OnCalendarTodosChanged(const Tizen::Base::Collection::IList& todoChangeInfoList);
	virtual void OnListViewItemLongPressed(Tizen::Ui::Controls::ListView& listView, int index, int elementId, bool& invokeListViewItemCallback);

private:
	static const int ID_FOOTER_CREATE = 100;
    static const int IDA_ITEM_DELETE                = 4001;

	Tizen::Base::Collection::IList* __pProfilesList;

	Tizen::Ui::Controls::ListView* __pProfileListView;
	Tizen::Io::Database *__pProfileDatabase;

	Tizen::Base::Collection::ArrayList __pTitleList;
	Tizen::Base::Collection::ArrayList __pIndexList;

	int __currentIndex;
    bool __isUpdateMode;

    void ListUpdate(void);
public:
    bool DeleteProfile(int index);

};

#endif  // _PROFILE_LIST_FORM_H_
