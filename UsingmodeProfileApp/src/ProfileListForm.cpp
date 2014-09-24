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
#include <FMedia.h>

#include "AppResourceId.h"
#include "SceneRegister.h"
#include "ProfileFormFactory.h"
#include "ProfileListForm.h"
#include "MockLocationListener.h"

using namespace Tizen::App;
using namespace Tizen::Base;
using namespace Tizen::Base::Collection;
using namespace Tizen::Graphics;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Ui::Scenes;
using namespace Tizen::Social;
using namespace Tizen::Io;
using namespace Tizen::System;

const wchar_t* SQL_CREATE = L"CREATE TABLE IF NOT EXISTS profile ( profileindex INTEGER PRIMARY KEY, name TEXT, startDateTime TEXT, dueDateTime TEXT, latitude DOUBLE, longitude DOUBLE, volume INTEGER, wifi INTEGER, memo TEXT )";
const wchar_t* SQL_INSERT = L"INSERT INTO profile(profileindex, name, startDateTime, dueDateTime, latitude, longitude, volume, wifi, memo) VALUES(?, ?, ?, ?, ?, ?, ?, ?, ?)";
const wchar_t* SQL_SELECT = L"SELECT name, startDateTime, dueDateTime, latitude, longitude, volume, wifi, memo FROM profile WHERE profileindex = ?";
const wchar_t* SQL_NAME_LIST = L"SELECT profileindex, name FROM profile";
const wchar_t* SQL_DELETE = L"DELETE FROM profile WHERE profileindex = ";
const wchar_t* SQL_UPDATE = L"UPDATE profile SET name = ?, startDateTime = ?, dueDateTime = ?, latitude = ?, longitude = ?, volume = ?, wifi = ?, memo = ? WHERE profileindex = ?";


ProfileListForm::ProfileListForm()
{
}

ProfileListForm::~ProfileListForm()
{
}

bool
ProfileListForm::Initialize(void)
{
	result r = E_SUCCESS;

	r = Construct(FORM_STYLE_NORMAL | FORM_STYLE_FOOTER | FORM_STYLE_HEADER | FORM_STYLE_PORTRAIT_INDICATOR);
	TryReturn(!IsFailed(r), false, "[%s] Failed to construct the form.", GetErrorMessage(r));
	SetName(FORM_LIST);

	// Database : db creation
	String dbName(App::GetInstance()->GetAppDataPath() + L"profile.db");
    __pProfileDatabase = new Database();
    __pProfileDatabase->Construct(dbName, "a+");

	__pProfileListView = null;
	__pTitleList.Construct();
    __pIndexList.Construct();

	return true;
}

result
ProfileListForm::OnInitializing(void)
{
	result r = E_SUCCESS;

	AppResource * pAppResource = Application::GetInstance()->GetAppResource();
	String resourceString;

	SetFormBackEventListener(this);

	// Header
	Header* pHeader = GetHeader();
	AppAssert(pHeader);
	pHeader->SetStyle(HEADER_STYLE_TITLE);
	pAppResource->GetString(IDS_HEADER_TITLE, resourceString);
	pHeader->SetTitleText(resourceString);

	// Footer
	Footer* pFooter = GetFooter();
	AppAssert(pFooter);
	pFooter->SetStyle(FOOTER_STYLE_BUTTON_TEXT);
	FooterItem footerCreate;
	footerCreate.Construct(ID_FOOTER_CREATE);
	pAppResource->GetString(IDS_FOOTER_CREATE, resourceString);
	footerCreate.SetText(resourceString);
	pFooter->AddItem(footerCreate);
	pFooter->AddActionEventListener(*this);

	__pProfileListView = new (std::nothrow) ListView();
	__pProfileListView->Construct(Rectangle(0, 0, GetClientAreaBounds().width, GetClientAreaBounds().height));
	pAppResource->GetString(IDS_EMPTY_LIST, resourceString);
	__pProfileListView->SetTextOfEmptyList(resourceString);
	__pProfileListView->SetItemProvider(*this);
	__pProfileListView->AddListViewItemEventListener(*this);
	__pProfileListView->SetSweepEnabled(true);
	AddControl(__pProfileListView);

	// Database: SQL Create
	String sql(SQL_CREATE);
	r = __pProfileDatabase->ExecuteSql(sql, true);
	if (IsFailed(r)) {
		AppLog("DB Creation Fail!!!");
	}
    __pTitleList.RemoveAll(true);
    __pIndexList.RemoveAll(true);

	SettingInfo::AddSettingEventListener(*this);
	
    ListUpdate();

	return r;
}

result
ProfileListForm::OnTerminating(void)
{
	result r = E_SUCCESS;

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
    // TODO: should be checked!!
}

void
ProfileListForm::OnListViewItemStateChanged(Tizen::Ui::Controls::ListView& listView, int index, int elementId, Tizen::Ui::Controls::ListItemStatus status)
{
	if (status == LIST_ITEM_STATUS_SELECTED)
	{
	    result r= E_SUCCESS;
	    SceneManager* pSceneManager = SceneManager::GetInstance();
		AppAssert(pSceneManager);

		ArrayList* pList = new (std::nothrow) ArrayList();
		pList->Construct();

	    DbEnumerator* pEnum;
	    DbStatement* pStmt;

	    // Database: SQL select row
	    pStmt = __pProfileDatabase->CreateStatementN(SQL_SELECT);

	    Integer* profileIndex = static_cast<Integer*>(__pIndexList.GetAt(index));  // index - List Index, profileIndex - Profile Index
	    r = pStmt->BindInt(0, profileIndex->ToInt());

	    pEnum = __pProfileDatabase->ExecuteStatementN(*pStmt);
	    if (pEnum) {
	    	_profile_t_ selectedProfile;
	        pEnum->MoveNext();

	        // 0. Profile Index (Not List Index)
	        pList->Add(*new (std::nothrow) Integer(*profileIndex));

	        // 1. Profile Name
	        r = pEnum->GetStringAt(0, selectedProfile.name);
	        if (r == E_SUCCESS) {
	        	pList->Add(*new (std::nothrow) String(selectedProfile.name));
	        } else {
	        	pList->Add(*new (std::nothrow) String(""));
	        }

	        // 2. Profile Start Date
	        r = pEnum->GetDateTimeAt(1, selectedProfile.startDateTime);
	        if (r == E_SUCCESS) {
	        	pList->Add(*new (std::nothrow) String(selectedProfile.startDateTime.ToString()));
	        } else {
	        	pList->Add(*new (std::nothrow) String(""));
	        }

	        // 3. Profile Due Date
	        r = pEnum->GetDateTimeAt(2, selectedProfile.dueDateTime);
	        if (r == E_SUCCESS) {
	        	pList->Add(*new (std::nothrow) String(selectedProfile.dueDateTime.ToString()));
	        } else {
	        	pList->Add(*new (std::nothrow) String(""));
	        }

	        // 4. Profile Location(Latitude)
	        r = pEnum->GetDoubleAt(3, selectedProfile.latitude);
			AppLog("r[[[[  %.2f  ]]]]]]", selectedProfile.latitude);
	        if (r == E_SUCCESS) {
	  		    pList->Add(*new (std::nothrow) Double(selectedProfile.latitude));
	        } else {
	        	pList->Add(*new (std::nothrow) Double(0));
	        }

	        // 5. Profile Location(Longitude)
	        r = pEnum->GetDoubleAt(4, selectedProfile.longitude);
	        if (r == E_SUCCESS) {
	        	pList->Add(*new (std::nothrow) Double(selectedProfile.longitude));
	        } else {
	        	pList->Add(*new (std::nothrow) Double(0));
	        }

	        // 6. Profile Volume
	        r = pEnum->GetIntAt(5, selectedProfile.volume.value);
	        if (r == E_SUCCESS) {
	        	pList->Add(*new (std::nothrow) Integer(selectedProfile.volume));
	        } else {
	        	pList->Add(*new (std::nothrow) Integer(0));
	        }

	        // 7. Profile Wifi
	        r = pEnum->GetIntAt(6, selectedProfile.wifi.value);
	        if (r == E_SUCCESS) {
	        	pList->Add(*new (std::nothrow) Integer(selectedProfile.wifi));
	        } else {
	        	pList->Add(*new (std::nothrow) Integer(0));
	        }
	        // 8. Profile Memo
	        r = pEnum->GetStringAt(7, selectedProfile.memo);
	        if (r == E_SUCCESS) {
	        	pList->Add(*new (std::nothrow) String(selectedProfile.memo));
	        } else {
	        	pList->Add(*new (std::nothrow) String(""));
	        }
	        delete pEnum;
	    }
	    delete pStmt;
		pSceneManager->GoForward(ForwardSceneTransition(SCENE_DETAIL), pList);
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
    	Integer* itemId = static_cast<Integer*>(__pIndexList.GetAt(index));
    	DeleteProfile(itemId->value);
    }
}

bool
ProfileListForm::DeleteProfile(int index)
{
    String getDeleteProfileMsg, getDialogTitle;
	AppResource * pAppResource = Application::GetInstance()->GetAppResource();
	pAppResource->GetString(IDS_DELETE_PROFILE, getDeleteProfileMsg);
	pAppResource->GetString(IDS_DIALOG_TITLE, getDialogTitle);

    int modalResult = 0;

    MessageBox msgbox;
    msgbox.Construct(getDialogTitle, getDeleteProfileMsg, MSGBOX_STYLE_YESNO, 3000);
    msgbox.ShowAndWait(modalResult);
    switch(modalResult){
    case MSGBOX_RESULT_YES:
        {
        	// Database: SQL Delete row
            String sql(SQL_DELETE);
            sql.Append(index);
            __pProfileDatabase->BeginTransaction();
            __pProfileDatabase->ExecuteSql(sql, true);
            __pProfileDatabase->CommitTransaction();
            ListUpdate();
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

	String getDelete;
	Application::GetInstance()->GetAppResource()->GetString(IDS_DELETE, getDelete);
    ListContextItem* pContextItem = new ListContextItem();
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
    pEnum = __pProfileDatabase->QueryN(SQL_NAME_LIST);
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
ProfileListForm::UpdateUsingmodeProfile(_profile_t_ profileSave)
{
    DbStatement* pStmt;
    DbEnumerator* pEnum;
    __pProfileDatabase->BeginTransaction();

	// Database: SQL Update row
	pStmt = __pProfileDatabase->CreateStatementN(SQL_UPDATE);
	if (pStmt != null) {
		AppLog("u[[[[  %.2f  ]]]]]]", profileSave.latitude);
		pStmt->BindString(0, profileSave.name);
		pStmt->BindString(1, profileSave.startDateTime.ToString());
		pStmt->BindString(2, profileSave.dueDateTime.ToString());
		pStmt->BindDouble(3, profileSave.latitude);
		pStmt->BindDouble(4, profileSave.longitude);
		pStmt->BindInt(5, profileSave.volume.ToInt());
		pStmt->BindInt(6, profileSave.wifi.ToInt());
		pStmt->BindString(7, profileSave.memo);
		pStmt->BindInt(8, profileSave.index.ToInt());

		pEnum = __pProfileDatabase->ExecuteStatementN(*pStmt);
		__pProfileDatabase->CommitTransaction();

		delete pStmt;
	    delete pEnum;
	}

    ListUpdate();
}

void
ProfileListForm::SaveUsingmodeProfile(_profile_t_ profileSave)
{
    DbStatement* pStmt;
    DbEnumerator* pEnum;
    __pProfileDatabase->BeginTransaction();

	// Datebase: SQL Insert row
	pStmt = __pProfileDatabase->CreateStatementN(SQL_INSERT);
	if (pStmt != null) {
		AppLog("s[[[[  %.2f  ]]]]]]", profileSave.latitude);
		pStmt->BindInt(0, profileSave.index.ToInt());
		pStmt->BindString(1, profileSave.name);
		pStmt->BindString(2, profileSave.startDateTime.ToString());
		pStmt->BindString(3, profileSave.dueDateTime.ToString());
		pStmt->BindDouble(4, profileSave.latitude);
		pStmt->BindDouble(5, profileSave.longitude);
		pStmt->BindInt(6, profileSave.volume.ToInt());
		pStmt->BindInt(7, profileSave.wifi.ToInt());
		pStmt->BindString(8, profileSave.memo);

		pEnum = __pProfileDatabase->ExecuteStatementN(*pStmt);
		__pProfileDatabase->CommitTransaction();

		delete pStmt;
		delete pEnum;
	}
    AppLog("-------end");

    ListUpdate();
}


void
ProfileListForm::OnSettingChanged (Tizen::Base::String &key)
{
	MockLocationListener *pMockLocationListner = new MockLocationListener();

	if(key == L"http://tizen.org/setting/sound.system.volume")
	{
	         AppLog("volume1");
	}
	else if(key == L"http://tizen.org/setting/sound.ringtone.volume")
	{
	        AppLog("volume2");
	        pMockLocationListner->StartApp();
	}

}
