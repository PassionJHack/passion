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

#include <new>
#include <FApp.h>
#include <FSystem.h>

#include "AppResourceId.h"
#include "ProfileListForm.h"
#include "SceneRegister.h"
#include "ProfileFormFactory.h"

using namespace Tizen::App;
using namespace Tizen::Base;
using namespace Tizen::Base::Collection;
using namespace Tizen::Graphics;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Ui::Scenes;
using namespace Tizen::Social;
using namespace Tizen::Io;

//static const int LIST_HEIGHT = 112;
//static const int BUTTON_HEIGHT = 74;

ProfileListForm::ProfileListForm()
//	: __pProfilesList(null)
//	, __pCalendarbook(null)
//	, __selectedStatus(TODO_STATUS_ALL)
	: __pProfileListView(null)
	, __isUpdateMode(false)
{
    __currentIndex = -1;
    __pTitleList.Construct();
    __pIndexList.Construct();
}

ProfileListForm::~ProfileListForm()
{
}

bool
ProfileListForm::Initialize(void)
{
	result r = E_SUCCESS;


    String dbName(App::GetInstance()->GetAppDataPath() + L"profile.db");
    __pProfileDatabase = new Database();
    __pProfileDatabase->Construct(dbName, "a+");


//	__pCalendarbook = new Calendarbook();
//	TryReturn(__pCalendarbook != null, false, "Failed to instantiate calendarbook.");
//
//	r = __pCalendarbook->Construct(*this);
//	if(IsFailed(r))
//	{
//		__pCalendarbook->Construct();
//		__pCalendarbook->GetLatestVersion();
//		r = GetLastResult();
//
//		MessageBox messageBox;
//
//		if(r == E_USER_NOT_CONSENTED)
//		{
//			messageBox.Construct(L"Error", L"The calendar privacy should be enabled.", MSGBOX_STYLE_OK);
//		}
//		else
//		{
//			messageBox.Construct(L"Error", L"Failed to construct the calendarbook.", MSGBOX_STYLE_OK);
//		}
//
//		int doModal;
//		messageBox.ShowAndWait(doModal);
//
//		UiApp* pApp = UiApp::GetInstance();
//		AppAssert(pApp);
//		pApp->Terminate();
//	}
//

	r = Construct(FORM_STYLE_NORMAL | FORM_STYLE_FOOTER | FORM_STYLE_HEADER | FORM_STYLE_PORTRAIT_INDICATOR);
	TryReturn(!IsFailed(r), false, "[%s] Failed to construct the form.", GetErrorMessage(r));
	SetName(FORM_LIST);

	return true;
}

result
ProfileListForm::OnInitializing(void)
{
	result r = E_SUCCESS;

	Header* pHeader = GetHeader();
	AppAssert(pHeader);
	pHeader->SetStyle(HEADER_STYLE_TITLE);
	String getHeaderTitle;
	Application::GetInstance()->GetAppResource()->GetString(IDS_HEADER_TITLE, getHeaderTitle);
	pHeader->SetTitleText(getHeaderTitle);

	Footer* pFooter = GetFooter();
	AppAssert(pFooter);
	pFooter->SetStyle(FOOTER_STYLE_BUTTON_TEXT);

	FooterItem footerCreate;
	footerCreate.Construct(ID_FOOTER_CREATE);
	String getFooterCreate;
	UiApp::GetInstance()->GetAppResource()->GetString(IDS_FOOTER_CREATE, getFooterCreate);
	footerCreate.SetText(getFooterCreate);
	pFooter->AddItem(footerCreate);
	pFooter->AddActionEventListener(*this);

	SetFormBackEventListener(this);

	String sql (L"CREATE TABLE IF NOT EXISTS profile(id INTEGER PRIMARY KEY, "
			"title TEXT, "
			"year INTEGER, month INTEGER, day INTEGER, hour INTEGER, minute INTEGER, "
			"year2 INTEGER, month2 INTEGER, day2 INTEGER, hour2 INTEGER, minute2 INTEGER, "
			"latitude INTEGER, longitude INTEGER, volume INTEGER, wifi INTEGER, memo TEXT)");
	__pProfileDatabase->ExecuteSql(sql, true);
    __pTitleList.RemoveAll(true);
    __pIndexList.RemoveAll(true);

//    static const int UI_POSITION_GAP = 0;

//	__pStatusContextButton = new (std::nothrow) Button();
//	__pStatusContextButton->Construct(Rectangle(GetClientAreaBounds().width * 2 / 3, UI_POSITION_GAP, GetClientAreaBounds().width / 3, BUTTON_HEIGHT), L"All");
//	__pStatusContextButton->SetActionId(ID_BUTTON_STATUS);
//	__pStatusContextButton->AddActionEventListener(*this);
//	AddControl(__pStatusContextButton);
//
//	__pStatusContextMenu = new (std::nothrow) ContextMenu();
//	__pStatusContextMenu->Construct(Point(GetClientAreaBounds().width * 5 / 6, BUTTON_HEIGHT * 3), CONTEXT_MENU_STYLE_LIST);
//	__pStatusContextMenu->AddItem(L"All", ID_CONTEXT_STATUS_ALL);
//	__pStatusContextMenu->AddItem(L"None", ID_CONTEXT_STATUS_NONE);
//	__pStatusContextMenu->AddItem(L"Needs action", ID_CONTEXT_STATUS_NEEDS_ACTION);
//	__pStatusContextMenu->AddItem(L"Completed", ID_CONTEXT_STATUS_COMPLETED);
//	__pStatusContextMenu->AddItem(L"In process", ID_CONTEXT_STATUS_IN_PROCESS);
//	__pStatusContextMenu->AddItem(L"Cancelled", ID_CONTEXT_STATUS_CANCELLED);
//	__pStatusContextMenu->AddActionEventListener(*this);

	__pProfileListView = new (std::nothrow) ListView();
	__pProfileListView->Construct(Rectangle(0 /*UI_POSITION_GAP*/, 0/*BUTTON_HEIGHT*/, GetClientAreaBounds().width, GetClientAreaBounds().height /*- BUTTON_HEIGHT*/));
	String getNoList;
	Application::GetInstance()->GetAppResource()->GetString(IDS_EMPTY_LIST, getNoList);
	__pProfileListView->SetTextOfEmptyList(getNoList);
	__pProfileListView->SetItemProvider(*this);
	__pProfileListView->AddListViewItemEventListener(*this);
	__pProfileListView->SetSweepEnabled(true);

	AddControl(__pProfileListView);

	ListUpdate();

//	__selectedStatus = TODO_STATUS_ALL;

	return r;
}

result
ProfileListForm::OnTerminating(void)
{
	result r = E_SUCCESS;

//	delete __pCalendarbook;
//
//	if (__pProfilesList != null)
//	{
//		__pProfilesList->RemoveAll(true);
//		delete __pProfilesList;
//	}

//	__pStatusContextMenu->Destroy();

	return r;
}

void
ProfileListForm::OnActionPerformed(const Tizen::Ui::Control& source, int actionId)
{

	SceneManager* pSceneManager = SceneManager::GetInstance();
	AppAssert(pSceneManager);

	switch (actionId)
	{
	case ID_FOOTER_CREATE:
		pSceneManager->GoForward(ForwardSceneTransition(SCENE_CREATION));
		break;
/*
	case ID_BUTTON_STATUS:
		__pStatusContextMenu->SetFocusable(true);
		__pStatusContextMenu->SetShowState(true);
		__pStatusContextMenu->Show();
		break;

	case ID_CONTEXT_STATUS_NONE:
		__pStatusContextButton->SetText(L"None");
		__pStatusContextButton->Invalidate(false);
		__selectedStatus = TODO_STATUS_NONE;

		GetProfileList();
		__pProfileListView->UpdateList();
		break;

	case ID_CONTEXT_STATUS_NEEDS_ACTION:
		__pStatusContextButton->SetText(L"Needs action");
		__pStatusContextButton->Invalidate(false);
		__selectedStatus = TODO_STATUS_NEEDS_ACTION;

		GetProfileList();
		__pProfileListView->UpdateList();
		break;

	case ID_CONTEXT_STATUS_COMPLETED:
		__pStatusContextButton->SetText(L"Completed");
		__pStatusContextButton->Invalidate(false);
		__selectedStatus = TODO_STATUS_COMPLETED;

		GetProfileList();
		__pProfileListView->UpdateList();
		break;

	case ID_CONTEXT_STATUS_IN_PROCESS:
		__pStatusContextButton->SetText(L"In process");
		__pStatusContextButton->Invalidate(false);
		__selectedStatus = TODO_STATUS_IN_PROCESS;

		GetProfileList();
		__pProfileListView->UpdateList();
		break;

	case ID_CONTEXT_STATUS_CANCELLED:
		__pStatusContextButton->SetText(L"Cancelled");
		__pStatusContextButton->Invalidate(false);
		__selectedStatus = TODO_STATUS_CANCELLED;

		GetProfileList();
		__pProfileListView->UpdateList();
		break;

	case ID_CONTEXT_STATUS_ALL:
		__pStatusContextButton->SetText(L"All");
		__pStatusContextButton->Invalidate(false);
		__selectedStatus = TODO_STATUS_ALL;

		GetProfileList();
		__pProfileListView->UpdateList();
		break;
*/
	default:
		break;
	}
}

void
ProfileListForm::OnFormBackRequested(Tizen::Ui::Controls::Form& source)
{
	UiApp* pApp = UiApp::GetInstance();
	AppAssert(pApp);
	pApp->Terminate();
}

void
ProfileListForm::OnListViewItemLongPressed(Tizen::Ui::Controls::ListView& listView, int index, int elementId, bool& invokeListViewItemCallback)
{
    invokeListViewItemCallback = false;
    AppLog("OnListViewItemLongPressed.111");

    __currentIndex = index;
    __isUpdateMode = true;
    // TODO: should be checked
}

void
ProfileListForm::OnListViewItemStateChanged(Tizen::Ui::Controls::ListView& listView, int index, int elementId, Tizen::Ui::Controls::ListItemStatus status)
{
	if (status == LIST_ITEM_STATUS_SELECTED)
	{
	    AppLog("OnListViewItemLongPressed.2222");

	    SceneManager* pSceneManager = SceneManager::GetInstance();
		AppAssert(pSceneManager);

		ArrayList* pList = new (std::nothrow) ArrayList();
		pList->Construct();
	    result r= E_SUCCESS;
	    __currentIndex = index;

	    DbEnumerator* pEnum;
	    DbStatement* pStmt;

	    pStmt = __pProfileDatabase->CreateStatementN(L"SELECT title, "
	    		"year, month, day, hour, minute, "
	    		"year2, month2, day2, hour2, minute,2 "
	    				"latitude, longitude, volume, wifi, memo FROM profile WHERE id = ?");
	    Integer* itemId = static_cast<Integer*>(__pIndexList.GetAt(index));
	    pList->Add(*new (std::nothrow) Integer(index/**itemId*/));
	    r = pStmt->BindInt(0, itemId->ToInt());
	    pEnum = __pProfileDatabase->ExecuteStatementN(*pStmt);
	    if (pEnum) {
	        String title;
	        pEnum->MoveNext();
	        r = pEnum->GetStringAt(0, title);
		    pList->Add(*new (std::nothrow) String(title));
		    int intItem;
	        r = pEnum->GetIntAt(1, intItem);	//year
		    pList->Add(*new (std::nothrow) Integer(intItem));
	        r = pEnum->GetIntAt(2, intItem);	//month
		    pList->Add(*new (std::nothrow) Integer(intItem));
	        r = pEnum->GetIntAt(3, intItem);	//day
		    pList->Add(*new (std::nothrow) Integer(intItem));
	        r = pEnum->GetIntAt(4, intItem);	//hour
		    pList->Add(*new (std::nothrow) Integer(intItem));
	        r = pEnum->GetIntAt(5, intItem);	//minute
		    pList->Add(*new (std::nothrow) Integer(intItem));
	        r = pEnum->GetIntAt(6, intItem);	//year2
		    pList->Add(*new (std::nothrow) Integer(intItem));
	        r = pEnum->GetIntAt(7, intItem);	//month2
		    pList->Add(*new (std::nothrow) Integer(intItem));
	        r = pEnum->GetIntAt(8, intItem);	//day2
		    pList->Add(*new (std::nothrow) Integer(intItem));
	        r = pEnum->GetIntAt(9, intItem);	//hour2
		    pList->Add(*new (std::nothrow) Integer(intItem));
	        r = pEnum->GetIntAt(10, intItem);	//minute2
		    pList->Add(*new (std::nothrow) Integer(intItem));
	        r = pEnum->GetIntAt(11, intItem);	//latitude
		    pList->Add(*new (std::nothrow) Integer(intItem));
	        r = pEnum->GetIntAt(12, intItem);	//longitude
		    pList->Add(*new (std::nothrow) Integer(intItem));
	        r = pEnum->GetIntAt(13, intItem);	//volume
		    pList->Add(*new (std::nothrow) Integer(intItem));
	        r = pEnum->GetIntAt(14, intItem);	//wifi
		    pList->Add(*new (std::nothrow) Integer(intItem));
	        r = pEnum->GetStringAt(15, title);	//memo
		    pList->Add(*new (std::nothrow) String(title));
	        delete pEnum;
	    }
	    delete pStmt;
		pSceneManager->GoForward(ForwardSceneTransition(SCENE_DETAIL), pList);
	    __isUpdateMode = true;
	}
}

void
ProfileListForm::OnListViewItemSwept(Tizen::Ui::Controls::ListView& listView, int index, Tizen::Ui::Controls::SweepDirection direction)
{
}

void
ProfileListForm::OnListViewContextItemStateChanged(Tizen::Ui::Controls::ListView& listView, int index, int elementId, Tizen::Ui::Controls::ListContextItemStatus state)
{
    if (elementId == IDA_ITEM_DELETE) {
    	DeleteProfile(index);
    }
}
bool
ProfileListForm::DeleteProfile(int index)
{
    AppLog("State Changed!!!! - 2");
    MessageBox msgbox;
    String getDeleteProfileMsg, getDialogTitle;
    Application::GetInstance()->GetAppResource()->GetString(IDS_DELETE_PROFILE, getDeleteProfileMsg);
    Application::GetInstance()->GetAppResource()->GetString(IDS_DIALOG_TITLE, getDialogTitle);
    msgbox.Construct(getDialogTitle, getDeleteProfileMsg, MSGBOX_STYLE_YESNO, 3000);
    int modalResult = 0;
    msgbox.ShowAndWait(modalResult);
    switch(modalResult){
    case MSGBOX_RESULT_YES:
        {
            String sql;
            sql.Append(L"DELETE FROM profile WHERE id = ");
            Integer* itemId = static_cast<Integer*>(__pIndexList.GetAt(index));
            sql.Append(itemId->ToInt());
            __pProfileDatabase->BeginTransaction();
            __pProfileDatabase->ExecuteSql(sql, true);
            __pProfileDatabase->CommitTransaction();
            ListUpdate();
            __isUpdateMode = false;
        }
        return true;
    }
    return false;
}

void
ProfileListForm::OnItemReordered(Tizen::Ui::Controls::ListView& view, int oldIndex, int newIndex)
{
}

int
ProfileListForm::GetItemCount(void)
{
	return  __pTitleList.GetCount();
}

Tizen::Ui::Controls::ListItemBase*
ProfileListForm::CreateItem(int index, int itemWidth)
{

	SimpleItem* pItem = new SimpleItem();
	AppAssert(pItem);

    pItem->Construct(Tizen::Graphics::Dimension(itemWidth, 100), LIST_ANNEX_STYLE_DETAILED);

    String *str = static_cast<String*>(__pTitleList.GetAt(index));
    pItem->SetElement(*str, null);

    ListContextItem* pContextItem = new ListContextItem();
	String getDelete;
	Application::GetInstance()->GetAppResource()->GetString(IDS_DELETE, getDelete);
    pContextItem->Construct();
    pContextItem->AddElement(IDA_ITEM_DELETE, getDelete);
    pItem->SetContextItem(pContextItem);

	return pItem;
}

bool
ProfileListForm::DeleteItem(int index, Tizen::Ui::Controls::ListItemBase* pItem, int itemWidth)
{
	delete pItem;
    pItem = null;
	return true;
}

void
ProfileListForm::OnSceneActivatedN(const Tizen::Ui::Scenes::SceneId& previousSceneId, const Tizen::Ui::Scenes::SceneId& currentSceneId, Tizen::Base::Collection::IList* pArgs)
{
	__pProfileListView->UpdateList();
}

void
ProfileListForm::OnSceneDeactivated(const Tizen::Ui::Scenes::SceneId& currentSceneId, const Tizen::Ui::Scenes::SceneId& nextSceneId)
{
}

void
ProfileListForm::OnCalendarTodosChanged(const Tizen::Base::Collection::IList& ProfileChangeInfoList)
{
	__pProfileListView->UpdateList();
}

void
ProfileListForm::ListUpdate(void)
{
    int id;
    String title;

    __pTitleList.RemoveAll(true);
    __pIndexList.RemoveAll(true);

    DbEnumerator* pEnum;
    pEnum = __pProfileDatabase->QueryN(L"SELECT id, title FROM profile");
    if (pEnum) {
        while(pEnum->MoveNext() == E_SUCCESS) {
            pEnum->GetIntAt(0, id);
            pEnum->GetStringAt(1, title);
            __pIndexList.Add(new Integer(id));
            __pTitleList.Add(new String(title));
        }
        delete pEnum;
    }
    __pProfileListView->UpdateList();

    Draw();
    Show();
}

void
ProfileListForm::SaveUsingmodeProfile(Tizen::Base::String title,
		int year,
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
		Tizen::Base::String memo)
{
	AppLog("%s, %s", title.GetPointer(), memo.GetPointer());

    DbStatement* pStmt;
    DbEnumerator* pEnum;
    long long id;

    Tizen::System::SystemTime::GetTicks(id);
    __pProfileDatabase->BeginTransaction();

    if (__isUpdateMode) {
        pStmt = __pProfileDatabase->CreateStatementN(L"UPDATE profile SET title = ?, "
        		"year = ?, month = ?, day = ?, hour = ?, minute = ?, "
        		"year2 = ?, month2 = ?, day2 = ?, hour2 = ?, minute2 = ?, "
        		"latitude = ?, longitude = ?, volume = ?, wifi = ?, memo = ? WHERE id = ?");
        pStmt->BindString(0, title);
        pStmt->BindInt(1, year);
        pStmt->BindInt(2, month);
        pStmt->BindInt(3, day);
        pStmt->BindInt(4, hour);
        pStmt->BindInt(5, minute);
        pStmt->BindInt(6, year);
        pStmt->BindInt(7, month);
        pStmt->BindInt(8, day);
        pStmt->BindInt(9, hour);
        pStmt->BindInt(10, minute);
        pStmt->BindInt(11, latitude);
        pStmt->BindInt(12, longitude);
        pStmt->BindInt(13, volume);
        pStmt->BindInt(14, wifi);
        pStmt->BindString(15, memo);
        Integer* itemId = static_cast<Integer*>(__pIndexList.GetAt(__currentIndex));
        pStmt->BindInt(16, itemId->ToInt());
        __isUpdateMode = false;
    } else {
        AppLog("Normal Save");
        pStmt = __pProfileDatabase->CreateStatementN(L"INSERT INTO profile (id, title, "
        		"year, month, day, hour, minute, "
        		"year2, month2, day2, hour2, minute2, "
        				"latitude, longitude, volume, wifi, memo) VALUES(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");
        pStmt->BindInt(0, id);
        pStmt->BindString(1, title);
        pStmt->BindInt(2, year);
        pStmt->BindInt(3, month);
        pStmt->BindInt(4, day);
        pStmt->BindInt(5, hour);
        pStmt->BindInt(6, minute);
        pStmt->BindInt(7, year2);
        pStmt->BindInt(8, month2);
        pStmt->BindInt(9, day2);
        pStmt->BindInt(10, hour2);
        pStmt->BindInt(11, minute2);
        pStmt->BindInt(12, latitude);
        pStmt->BindInt(13, longitude);
        pStmt->BindInt(14, volume);
        pStmt->BindInt(15, wifi);
        pStmt->BindString(16, memo);
    }
    pEnum = __pProfileDatabase->ExecuteStatementN(*pStmt);
    __pProfileDatabase->CommitTransaction();

    delete pStmt;
    delete pEnum;
    ListUpdate();
}
