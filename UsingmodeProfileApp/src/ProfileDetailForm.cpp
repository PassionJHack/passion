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
#include <FLocales.h>

#include "AppResourceId.h"
#include "SceneRegister.h"
#include "ProfileFormFactory.h"
#include "ProfileDetailForm.h"
#include "ProfileListForm.h"

using namespace Tizen::App;
using namespace Tizen::Base;
using namespace Tizen::Base::Collection;
using namespace Tizen::Graphics;
using namespace Tizen::Locales;
using namespace Tizen::Social;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Ui::Scenes;

ProfileDetailForm::ProfileDetailForm()
{
}

ProfileDetailForm::~ProfileDetailForm()
{
}

bool
ProfileDetailForm::Initialize(void)
{
    result r = E_SUCCESS;

    Construct(FORM_STYLE_NORMAL | FORM_STYLE_FOOTER | FORM_STYLE_HEADER | FORM_STYLE_PORTRAIT_INDICATOR);
    TryReturn(r == E_SUCCESS, false, "[%s] Failed to construct the form.", GetErrorMessage(r));
    __currentID = -1;
    __latitude = 0;
    __longitude = 0;
    return true;
}

result
ProfileDetailForm::OnInitializing(void)
{
    result r = E_SUCCESS;
    AppResource * pAppResource = Application::GetInstance()->GetAppResource();
	String resourceString;

    // Header
    Header* pHeader = GetHeader();
    AppAssert(pHeader);
    pHeader->SetStyle(HEADER_STYLE_TITLE);
    pAppResource->GetString(IDS_DETAILS, resourceString);
    pHeader->SetTitleText(resourceString);

    // Footer
    Footer* pFooter = GetFooter();
    AppAssert(pFooter);
    pFooter->SetStyle(FOOTER_STYLE_BUTTON_TEXT);

    pAppResource->GetString(IDS_EDIT, resourceString);
    FooterItem footerEdit;
    footerEdit.Construct(ID_FOOTER_EDIT);
    footerEdit.SetText(resourceString);
    pFooter->AddItem(footerEdit);

    pAppResource->GetString(IDS_DELETE, resourceString);
    FooterItem footerDelete;
    footerDelete.Construct(ID_FOOTER_DELETE);
    footerDelete.SetText(resourceString);
    pFooter->AddItem(footerDelete);
    pFooter->AddActionEventListener(*this);

    SetFormBackEventListener(this);

    static const unsigned int COLOR_BACKGROUND_LABEL = 0xFFEFEDE5;
    static const unsigned int COLOR_TITLE_LABEL = 0xFF808080;

    static const int UI_X_POSITION_GAP = 20;
    static const int UI_WIDTH = GetClientAreaBounds().width - 40;
    static const int UI_X_POSITION_MIDDLE1 = UI_WIDTH / 2 + UI_X_POSITION_GAP;
    static const int UI_X_POSITION_MIDDLE2 = UI_WIDTH / 4 + UI_X_POSITION_GAP;
    static const int UI_HEIGHT = 112;
    static const int UI_SPACE = 26;
    int yPosition = 0;

    ScrollPanel* pScrollPanel = new (std::nothrow) ScrollPanel();
    pScrollPanel->Construct(Rectangle(0, 0, GetClientAreaBounds().width, GetClientAreaBounds().height));

    String date;
    DateTime displayStartDate;
    DateTime displayDueDate;

    // 1. Profile Name
    Label* pNameLabel = new (std::nothrow) Label();
    pAppResource->GetString(IDS_PROFILE_NAME, resourceString);
    pNameLabel->Construct(Rectangle(UI_X_POSITION_GAP, yPosition, UI_WIDTH, UI_HEIGHT), resourceString);
    pNameLabel->SetTextHorizontalAlignment(ALIGNMENT_LEFT);
    pNameLabel->SetTextColor(COLOR_TITLE_LABEL);
    pNameLabel->SetBackgroundColor(Color(COLOR_BACKGROUND_LABEL));
    pScrollPanel->AddControl(pNameLabel);
    __pNameLabelData = new (std::nothrow) Label();
    __pNameLabelData->Construct(Rectangle(UI_X_POSITION_MIDDLE1, yPosition, UI_WIDTH * 1 / 2, UI_HEIGHT), L"");
    __pNameLabelData->SetTextHorizontalAlignment(ALIGNMENT_LEFT);
    pScrollPanel->AddControl(__pNameLabelData);

    // 2. Profile Start Date
    Label* pStartDateLabel = new (std::nothrow) Label();
    pAppResource->GetString(IDS_START_DATETIME, resourceString);
    pStartDateLabel->Construct(Rectangle(UI_X_POSITION_GAP, yPosition += UI_HEIGHT + UI_SPACE, UI_WIDTH, UI_HEIGHT), resourceString);
    pStartDateLabel->SetTextHorizontalAlignment(ALIGNMENT_LEFT);
    pStartDateLabel->SetTextColor(COLOR_TITLE_LABEL);
    pStartDateLabel->SetBackgroundColor(Color(COLOR_BACKGROUND_LABEL));
    pScrollPanel->AddControl(pStartDateLabel);
    __pStartDateLabelData = new (std::nothrow) Label();
    __pStartDateLabelData->Construct(Rectangle(UI_X_POSITION_MIDDLE1, yPosition, UI_WIDTH * 1 / 2, UI_HEIGHT), L"");
    __pStartDateLabelData->SetTextHorizontalAlignment(ALIGNMENT_LEFT);
    pScrollPanel->AddControl(__pStartDateLabelData);

    // 3. Profile Due Date
    Label* pDueDateLabel = new (std::nothrow) Label();
    pAppResource->GetString(IDS_END_DATETIME, resourceString);
    pDueDateLabel->Construct(Rectangle(UI_X_POSITION_GAP, yPosition += UI_HEIGHT, UI_WIDTH, UI_HEIGHT), resourceString);
    pDueDateLabel->SetTextHorizontalAlignment(ALIGNMENT_LEFT);
    pDueDateLabel->SetTextColor(COLOR_TITLE_LABEL);
    pDueDateLabel->SetBackgroundColor(Color(COLOR_BACKGROUND_LABEL));
    pScrollPanel->AddControl(pDueDateLabel);
    __pDueDateLabelData = new (std::nothrow) Label();
    __pDueDateLabelData->Construct(Rectangle(UI_X_POSITION_MIDDLE1, yPosition, UI_WIDTH * 1 / 2, UI_HEIGHT), L"");
    __pDueDateLabelData->SetTextHorizontalAlignment(ALIGNMENT_LEFT);
    pScrollPanel->AddControl(__pDueDateLabelData);

    // 4~5. Profile Location(Latitude Longitude)
    Label* pLocationLabel = new (std::nothrow) Label();
    pAppResource->GetString(IDS_LOCATION, resourceString);
    pLocationLabel->Construct(Rectangle(UI_X_POSITION_GAP, yPosition += UI_HEIGHT + UI_SPACE, UI_WIDTH, UI_HEIGHT), resourceString);
    pLocationLabel->SetTextHorizontalAlignment(ALIGNMENT_LEFT);
    pLocationLabel->SetTextColor(COLOR_TITLE_LABEL);
    pLocationLabel->SetBackgroundColor(Color(COLOR_BACKGROUND_LABEL));
    pScrollPanel->AddControl(pLocationLabel);
    __pLocationLabelData = new (std::nothrow) Label();
    __pLocationLabelData->Construct(Rectangle(UI_X_POSITION_MIDDLE2, yPosition, UI_WIDTH * 3 / 4, UI_HEIGHT), L"");
    __pLocationLabelData->SetTextHorizontalAlignment(ALIGNMENT_LEFT);
    pScrollPanel->AddControl(__pLocationLabelData);

    // 6. Profile Volume
    Label* pVolumeLabel = new (std::nothrow) Label();
    pAppResource->GetString(IDS_VOLUME, resourceString);
    pVolumeLabel->Construct(Rectangle(UI_X_POSITION_GAP, yPosition += UI_HEIGHT + UI_SPACE, UI_WIDTH, UI_HEIGHT), resourceString);
    pVolumeLabel->SetTextHorizontalAlignment(ALIGNMENT_LEFT);
    pVolumeLabel->SetTextColor(COLOR_TITLE_LABEL);
    pVolumeLabel->SetBackgroundColor(Color(COLOR_BACKGROUND_LABEL));
    pScrollPanel->AddControl(pVolumeLabel);
    __pVolumeLabelData = new (std::nothrow) Label();
    __pVolumeLabelData->Construct(Rectangle(UI_X_POSITION_MIDDLE2, yPosition, UI_WIDTH * 3 / 4, UI_HEIGHT), L"");
    __pVolumeLabelData->SetTextHorizontalAlignment(ALIGNMENT_LEFT);
    pScrollPanel->AddControl(__pVolumeLabelData);

    // 7. Profile Wifi
    Label* pWifiLabel = new (std::nothrow) Label();
    pAppResource->GetString(IDS_WIFI, resourceString);
    pWifiLabel->Construct(Rectangle(UI_X_POSITION_GAP, yPosition += UI_HEIGHT, UI_WIDTH, UI_HEIGHT), resourceString);
    pWifiLabel->SetTextHorizontalAlignment(ALIGNMENT_LEFT);
    pWifiLabel->SetTextColor(COLOR_TITLE_LABEL);
    pWifiLabel->SetBackgroundColor(Color(COLOR_BACKGROUND_LABEL));
    pScrollPanel->AddControl(pWifiLabel);
    __pWifiLabelData = new (std::nothrow) Label();
    __pWifiLabelData->Construct(Rectangle(UI_X_POSITION_MIDDLE2, yPosition, UI_WIDTH * 3 / 4, UI_HEIGHT), L"");
    __pWifiLabelData->SetTextHorizontalAlignment(ALIGNMENT_LEFT);
    pScrollPanel->AddControl(__pWifiLabelData);

    // 8. Profile Description
    Label* pDescriptionLabel = new (std::nothrow) Label();
    pAppResource->GetString(IDS_DESCRIPTION, resourceString);
    pDescriptionLabel->Construct(Rectangle(UI_X_POSITION_GAP, yPosition += UI_HEIGHT + UI_SPACE, UI_WIDTH, UI_HEIGHT), resourceString);
    pDescriptionLabel->SetTextHorizontalAlignment(ALIGNMENT_LEFT);
    pDescriptionLabel->SetTextColor(COLOR_TITLE_LABEL);
    pDescriptionLabel->SetBackgroundColor(Color(COLOR_BACKGROUND_LABEL));
    pScrollPanel->AddControl(pDescriptionLabel);
    __pDescriptionLabelData = new (std::nothrow) Label();
    __pDescriptionLabelData->Construct(Rectangle(UI_X_POSITION_MIDDLE2, yPosition, UI_WIDTH * 3 / 4, UI_HEIGHT), L"");
    __pDescriptionLabelData->SetTextHorizontalAlignment(ALIGNMENT_LEFT);
    pScrollPanel->AddControl(__pDescriptionLabelData);

    AddControl(pScrollPanel);

    return r;
}

result
ProfileDetailForm::OnTerminating(void)
{
    result r = E_SUCCESS;

    return r;
}

void
ProfileDetailForm::OnActionPerformed(const Tizen::Ui::Control& source, int actionId)
{
    SceneManager* pSceneManager = SceneManager::GetInstance();
    AppAssert(pSceneManager);

    switch (actionId)
    {
    case ID_FOOTER_EDIT:
    {
        SceneManager* pSceneManager = SceneManager::GetInstance();
        AppAssert(pSceneManager);

        ArrayList* pList = new (std::nothrow) ArrayList();
        pList->Construct();
        pList->Add(*new (std::nothrow) Integer(__currentID));                        // 0. Profile Index : Not List Index
        pList->Add(*new (std::nothrow) String(__pNameLabelData->GetText()));         // 1. Profile Name
        pList->Add(*new (std::nothrow) String(__pStartDateLabelData->GetText()));    // 2. Profile Start Date
        pList->Add(*new (std::nothrow) String(__pDueDateLabelData->GetText()));      // 3. Profile Due Date
        pList->Add(*new (std::nothrow) Double(__latitude));                          // 4. Profile Location(Latitude)
        pList->Add(*new (std::nothrow) Double(__longitude));                         // 5. Profile Location(Longitude)
        int nVolume, nWiFi;
        Tizen::Base::Integer::Parse(__pVolumeLabelData->GetText(), nVolume);
        pList->Add(*new (std::nothrow) Integer(nVolume));                            // 6. Profile Volume
        Tizen::Base::Integer::Parse(__pWifiLabelData->GetText(), nWiFi);
        pList->Add(*new (std::nothrow) Integer(nWiFi));                              // 7. Profile Wifi
        pList->Add(*new (std::nothrow) String(__pDescriptionLabelData->GetText()));  // 8. Profile Memo
        pSceneManager->GoForward(ForwardSceneTransition(SCENE_EDITION), pList);
    }
    break;

    case ID_FOOTER_DELETE:
    {
        DeleteProfile();
    }
    break;

    default:
    {
    }
    break;
    }
}

void
ProfileDetailForm::OnFormBackRequested(Tizen::Ui::Controls::Form& source)
{
    SceneManager* pSceneManager = SceneManager::GetInstance();
    AppAssert(pSceneManager);

    pSceneManager->GoBackward(BackwardSceneTransition(SCENE_LIST));
}

void
ProfileDetailForm::OnSceneActivatedN(const Tizen::Ui::Scenes::SceneId& previousSceneId, const Tizen::Ui::Scenes::SceneId& currentSceneId, Tizen::Base::Collection::IList* pArgs)
{
    result r = E_SUCCESS;

    if (pArgs != null)
    {
        if (pArgs->GetCount() == 9) {
        	Integer* pId = static_cast< Integer* >(pArgs->GetAt(0));		// 0. Profile Index (Not List Index)
            __currentID = pId->ToInt();
            String* pNameValue = static_cast< String* >(pArgs->GetAt(1));	// 1. Profile Name
            if (pNameValue == null) {
                __pNameLabelData->SetText(L"");
            } else {
                __pNameLabelData->SetText(*pNameValue);
            }
            String* pStartDateString = static_cast< String* >(pArgs->GetAt(2));	// 2. Profile Start Date
            __pStartDateLabelData->SetText(*pStartDateString);
            String* pDueDateString = static_cast< String* >(pArgs->GetAt(3));	// 3. Profile Due Date
            __pDueDateLabelData->SetText(*pDueDateString);
            Double* pLatitude = static_cast< Double* >(pArgs->GetAt(4));		// 4. Profile Location(Latitude)
            Double* pLongitude = static_cast< Double* >(pArgs->GetAt(5));		// 5. Profile Location(Longitude)
        	String LocationString;
            __latitude = pLatitude->value;
            __longitude = pLongitude->value;
        	LocationString.Format(50, L"latitude: %.2f, longitude: %.2f", pLatitude->value, pLongitude->value);
            __pLocationLabelData->SetText(LocationString);
            Integer* pVolume = static_cast< Integer* >(pArgs->GetAt(6));		// 6. Profile Volume
            __pVolumeLabelData->SetText(pVolume->ToString());
            Integer* pWifi = static_cast< Integer* >(pArgs->GetAt(7));			// 7. Profile Wifi
            __pWifiLabelData->SetText(pWifi->ToInt()==1?"On":"Off");
            String* pMemo = static_cast< String* >(pArgs->GetAt(8));			// 8. Profile Memo
            String PropertyValue = L"";
            if (pMemo != null) {
                PropertyValue = *pMemo;
            }
            __pDescriptionLabelData->SetText(PropertyValue);

            Invalidate(true);

            pArgs->RemoveAll(true);
            delete pArgs;

            return;
        }
    }

    if (__currentID == -1) {
		MessageBox messageBox;
		AppResource * pAppResource = Application::GetInstance()->GetAppResource();
		String getError, getFailGet;
		pAppResource->GetString(IDS_ERROR, getError);
		pAppResource->GetString(IDS_FAIL_GET, getFailGet);
		messageBox.Construct(getError, getFailGet, MSGBOX_STYLE_OK, 0);
		int doModal;
		messageBox.ShowAndWait(doModal);

		AppLogException("[%s] Failed to get Profile.", GetErrorMessage(r));
    }
}

void
ProfileDetailForm::OnSceneDeactivated(const Tizen::Ui::Scenes::SceneId& currentSceneId, const Tizen::Ui::Scenes::SceneId& nextSceneId)
{
}

void
ProfileDetailForm::DeleteProfile(void)
{
    ProfileListForm *pProfileListForm = static_cast< ProfileListForm* >(Application::GetInstance()->GetAppFrame()->GetFrame()->GetControl(FORM_LIST));
    if (pProfileListForm != NULL)
    {
        if (pProfileListForm->DeleteProfile(__currentID))
        {
            SceneManager* pSceneManager = SceneManager::GetInstance();
            AppAssert(pSceneManager);

            pSceneManager->GoBackward(BackwardSceneTransition(SCENE_LIST));
        }
    }
    else
    {
        MessageBox messageBox;
        AppResource * pAppResource = Application::GetInstance()->GetAppResource();
        String getError, getFailDelete;
        pAppResource->GetString(IDS_ERROR, getError);
        pAppResource->GetString(IDS_FAIL_DELETE, getFailDelete);
        messageBox.Construct(getError, getFailDelete, MSGBOX_STYLE_OK, 0);
        int doModal;
        messageBox.ShowAndWait(doModal);
    }
}
