// NewUIEnterBloodCastle.cpp: implementation of the CNewUIPartyInfo class.
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "I18N/All.h"

#include "UI/NewUI/Events/NewUIEnterDevilSquare.h"
#include "UI/NewUI/NewUISystem.h"
#include "Engine/Object/ZzzCharacter.h"
#include "Character/CharacterManager.h"
#include "Audio/DSPlaySound.h"

using namespace SEASON3B;

CNewUIEnterDevilSquare::CNewUIEnterDevilSquare()
{
    m_pNewUIMng = NULL;
    memset(&m_Pos, 0, sizeof(POINT));
    memset(&m_EnterUITextPos, 0, sizeof(POINT));

    m_iNumActiveBtn = 1;
    m_BtnEnterStartPos.x = m_BtnEnterStartPos.y = 0;
    m_dwBtnTextColor[0] = RGBA(150, 150, 150, 255);
    m_dwBtnTextColor[1] = RGBA(255, 255, 255, 255);

    m_iDevilSquareLimitLevel[0][0] = 15; m_iDevilSquareLimitLevel[0][1] = 130;
    m_iDevilSquareLimitLevel[1][0] = 131; m_iDevilSquareLimitLevel[1][1] = 180;
    m_iDevilSquareLimitLevel[2][0] = 181; m_iDevilSquareLimitLevel[2][1] = 230;
    m_iDevilSquareLimitLevel[3][0] = 231; m_iDevilSquareLimitLevel[3][1] = 280;
    m_iDevilSquareLimitLevel[4][0] = 281; m_iDevilSquareLimitLevel[4][1] = 330;
    m_iDevilSquareLimitLevel[5][0] = 331; m_iDevilSquareLimitLevel[5][1] = 400;
    m_iDevilSquareLimitLevel[6][0] = 0; m_iDevilSquareLimitLevel[6][1] = 0;

    m_iDevilSquareLimitLevel[7][0] = 15; m_iDevilSquareLimitLevel[7][1] = 110;
    m_iDevilSquareLimitLevel[8][0] = 111; m_iDevilSquareLimitLevel[8][1] = 160;
    m_iDevilSquareLimitLevel[9][0] = 161; m_iDevilSquareLimitLevel[9][1] = 210;
    m_iDevilSquareLimitLevel[10][0] = 211; m_iDevilSquareLimitLevel[10][1] = 260;
    m_iDevilSquareLimitLevel[11][0] = 261; m_iDevilSquareLimitLevel[11][1] = 310;
    m_iDevilSquareLimitLevel[12][0] = 311; m_iDevilSquareLimitLevel[12][1] = 400;
    m_iDevilSquareLimitLevel[13][0] = 0; m_iDevilSquareLimitLevel[13][1] = 0;
}

CNewUIEnterDevilSquare::~CNewUIEnterDevilSquare()
{
    Release();
}

bool CNewUIEnterDevilSquare::Create(CNewUIManager* pNewUIMng, int x, int y)
{
    if (NULL == pNewUIMng)
        return false;

    m_pNewUIMng = pNewUIMng;
    m_pNewUIMng->AddUIObj(SEASON3B::INTERFACE_DEVILSQUARE, this);

    SetPos(x, y);

    LoadImages();

    // Exit Button
    m_BtnExit.ChangeButtonImgState(true, IMAGE_ENTERDS_BASE_WINDOW_BTN_EXIT, false);
    m_BtnExit.ChangeButtonInfo(m_Pos.x + 13, m_Pos.y + 392, 36, 29);
    m_BtnExit.ChangeToolTipText(&I18N::Game::Close388, true);

    // Enter Button
    int iVal = 0;
    for (int i = 0; i < MAX_ENTER_GRADE; i++)
    {
        iVal = ENTER_BTN_VAL * i;
        m_BtnEnter[i].ChangeButtonImgState(true, IMAGE_ENTERDS_BASE_WINDOW_BTN_ENTER, true);
        m_BtnEnter[i].ChangeButtonInfo(m_BtnEnterStartPos.x, m_BtnEnterStartPos.y + iVal, 180, 29);
    }

    Show(false);

    return true;
}

void CNewUIEnterDevilSquare::Release()
{
    UnloadImages();

    if (m_pNewUIMng)
    {
        m_pNewUIMng->RemoveUIObj(this);
        m_pNewUIMng = NULL;
    }
}

void CNewUIEnterDevilSquare::SetPos(int x, int y)
{
    m_Pos.x = x;
    m_Pos.y = y;
    m_EnterUITextPos.x = m_Pos.x + 3;
    m_EnterUITextPos.y = m_Pos.y + 45;

    SetBtnPos(m_Pos.x + 6, m_Pos.y + 155);

    m_BtnExit.ChangeButtonInfo(m_Pos.x + 13, m_Pos.y + 392, 36, 29);

    for (int i = 0; i < MAX_ENTER_GRADE; i++)
    {
        int iVal = ENTER_BTN_VAL * i;
        m_BtnEnter[i].ChangeButtonInfo(m_BtnEnterStartPos.x, m_BtnEnterStartPos.y + iVal, 180, 29);
    }
}

void CNewUIEnterDevilSquare::SetBtnPos(int x, int y)
{
    m_BtnEnterStartPos.x = x;
    m_BtnEnterStartPos.y = y;
}

bool CNewUIEnterDevilSquare::UpdateMouseEvent()
{
    if (true == BtnProcess())
        return false;

    if (CheckMouseIn(m_Pos.x, m_Pos.y, ENTERDS_BASE_WINDOW_WIDTH, ENTERDS_BASE_WINDOW_HEIGHT))
        return false;

    return true;
}

bool CNewUIEnterDevilSquare::UpdateKeyEvent()
{
    if (g_pNewUISystem->IsVisible(SEASON3B::INTERFACE_DEVILSQUARE) == true)
    {
        if (SEASON3B::IsPress(VK_ESCAPE) == true)
        {
            g_pNewUISystem->Hide(SEASON3B::INTERFACE_DEVILSQUARE);
            PlayBuffer(SOUND_CLICK01);
            return false;
        }
    }

    return true;
}

bool CNewUIEnterDevilSquare::Update()
{
    if (!IsVisible())
        return true;

    return true;
}

bool CNewUIEnterDevilSquare::Render()
{
    EnableAlphaTest();

    RenderImage(IMAGE_ENTERDS_BASE_WINDOW_BACK, m_Pos.x, m_Pos.y, float(ENTERDS_BASE_WINDOW_WIDTH), float(ENTERDS_BASE_WINDOW_HEIGHT));
    RenderImage(IMAGE_ENTERDS_BASE_WINDOW_TOP, m_Pos.x, m_Pos.y, float(ENTERDS_BASE_WINDOW_WIDTH), 64.f);
    RenderImage(IMAGE_ENTERDS_BASE_WINDOW_LEFT, m_Pos.x, m_Pos.y + 64.f, 21.f, float(ENTERDS_BASE_WINDOW_HEIGHT) - 64.f - 45.f);
    RenderImage(IMAGE_ENTERDS_BASE_WINDOW_RIGHT, m_Pos.x + float(ENTERDS_BASE_WINDOW_WIDTH) - 21.f, m_Pos.y + 64.f, 21.f, float(ENTERDS_BASE_WINDOW_HEIGHT) - 64.f - 45.f);
    RenderImage(IMAGE_ENTERDS_BASE_WINDOW_BOTTOM, m_Pos.x, m_Pos.y + float(ENTERDS_BASE_WINDOW_HEIGHT) - 45.f, float(ENTERDS_BASE_WINDOW_WIDTH), 45.f);

    g_pRenderText->SetFont(g_hFontBold);
    g_pRenderText->SetTextColor(0xFFFFFFFF);
    g_pRenderText->SetBgColor(0x00000000);
    g_pRenderText->RenderText(m_Pos.x + 60, m_Pos.y + 12, I18N::Game::DevilSquare, 72, 0, RT3_SORT_CENTER);
    g_pRenderText->SetFont(g_hFont);
    g_pRenderText->RenderText(m_EnterUITextPos.x, m_EnterUITextPos.y, I18N::Game::YouVeBeenGivenAChanceToProveYourBravery, 190, 0, RT3_SORT_CENTER);
    g_pRenderText->RenderText(m_EnterUITextPos.x, m_EnterUITextPos.y + 15, I18N::Game::NoOneHasEverEnteredTheDevilSquareYet, 190, 0, RT3_SORT_CENTER);
    g_pRenderText->RenderText(m_EnterUITextPos.x, m_EnterUITextPos.y + 30, I18N::Game::NoHumanHasEverGoneThere, 190, 0, RT3_SORT_CENTER);
    g_pRenderText->RenderText(m_EnterUITextPos.x, m_EnterUITextPos.y + 45, I18N::Game::DoNotBelieveAnythingYouSeeInThere, 190, 0, RT3_SORT_CENTER);
    g_pRenderText->RenderText(m_EnterUITextPos.x, m_EnterUITextPos.y + 60, I18N::Game::OnlyTrustYourBraveryAndStrength, 190, 0, RT3_SORT_CENTER);
    g_pRenderText->RenderText(m_EnterUITextPos.x, m_EnterUITextPos.y + 75, I18N::Game::OnlyYourBraveryAndStrengthWillKeepYouAlive, 190, 0, RT3_SORT_CENTER);

    for (int i = 0; i < MAX_ENTER_GRADE; i++)
    {
        m_BtnEnter[i].Render();
    }

    // Exit Button
    m_BtnExit.Render();

    DisableAlphaBlend();

    return true;
}

//---------------------------------------------------------------------------------------------
// BtnProcess
bool CNewUIEnterDevilSquare::BtnProcess()
{
    // Top-right corner close "X" (shared frame). Hides + swallows the click.
    if (g_pNewUISystem->HandleFrameCornerClose(m_Pos, SEASON3B::INTERFACE_DEVILSQUARE))
        return true;

    if (m_BtnExit.UpdateMouseEvent() == true)
    {
        g_pNewUISystem->Hide(SEASON3B::INTERFACE_DEVILSQUARE);
        return true;
    }

    // Every level is selectable - the server is the one that decides whether this character
    // qualifies (by resets, not character level here), and answers with a clear message if not.
    // Previously only the single button matching the character's level bracket (m_iNumActiveBtn,
    // from the legacy level-range table above) was ever unlocked/clickable, so a character outside
    // that one bracket saw every other level as permanently locked regardless of resets - same bug
    // Blood Castle's entry window had (see NewUIBloodCastleEnter.cpp).
    for (int i = 0; i < MAX_ENTER_GRADE; ++i)
    {
        if (m_BtnEnter[i].UpdateMouseEvent() == true)
        {
            SocketClient->ToGameServer()->SendDevilSquareEnterRequest(i, 0xFF);
            g_pNewUISystem->Hide(SEASON3B::INTERFACE_DEVILSQUARE);
            break;
        }
    }

    return false;
}

float CNewUIEnterDevilSquare::GetLayerDepth()
{
    return 4.0f;
}

int CNewUIEnterDevilSquare::CheckLimitLV(int iIndex)
{
    int	iVal = 0;
    int iRet = 0;

    if (iIndex == 1)
    {
        iVal = 7;
    }

    int iLevel;
    if (gCharacterManager.IsMasterLevel(CharacterAttribute->Class) == true)
        iLevel = Master_Level_Data.nMLevel;
    else
        iLevel = CharacterAttribute->Level;
    //Master_Level_Data.nMLevel

    if (gCharacterManager.IsMasterLevel(CharacterAttribute->Class) == false)
    {
        for (int iCastleLV = 0; iCastleLV < MAX_ENTER_GRADE - 1; ++iCastleLV)
        {
            if (iLevel >= m_iDevilSquareLimitLevel[iVal + iCastleLV][0]
                && iLevel <= m_iDevilSquareLimitLevel[iVal + iCastleLV][1])
            {
                iRet = iCastleLV;
                break;
            }
        }
    }
    else
        iRet = MAX_ENTER_GRADE - 1;

    return iRet;
}

void CNewUIEnterDevilSquare::OpenningProcess()
{
    SocketClient->ToGameServer()->SendCloseNpcRequest();

    // Every level starts unlocked - resets (checked server-side), not character level, decide
    // whether entry actually succeeds. m_iNumActiveBtn/CheckLimitLV's level-bracket table is no
    // longer used to gate buttons (kept only because CheckLimitLV/m_iDevilSquareLimitLevel remain
    // referenced elsewhere); labels below are tier-based instead of level-range-based now too.
    for (int i = 0; i < MAX_ENTER_GRADE; i++)
    {
        m_BtnEnter[i].ChangeTextColor(m_dwBtnTextColor[ENTERBTN_ENABLE]);
        m_BtnEnter[i].UnLock();
    }

    int iLimitLVIndex = 0;
    if (gCharacterManager.GetBaseClass(Hero->Class) == CLASS_DARK || gCharacterManager.GetBaseClass(Hero->Class) == CLASS_DARK_LORD
        || gCharacterManager.GetBaseClass(Hero->Class) == CLASS_RAGEFIGHTER)
    {
        iLimitLVIndex = 1;
    }

    m_iNumActiveBtn = CheckLimitLV(iLimitLVIndex);

    // Same tier scale as Blood Castle's entry window (NewUIBloodCastleEnter.cpp) - Devil Square
    // only has 7 levels (no equivalent of Blood Castle's extra 8th/hardest one), so it tops out at
    // Tier 4 instead of Tier 4.5.
    const wchar_t* const tierLabels[MAX_ENTER_GRADE] =
    {
        I18N::Game::TierLabel1, I18N::Game::TierLabel1Point5, I18N::Game::TierLabel2, I18N::Game::TierLabel2Point5,
        I18N::Game::TierLabel3, I18N::Game::TierLabel3Point5, I18N::Game::TierLabel4,
    };

    for (int i = 0; i < MAX_ENTER_GRADE; i++)
    {
        m_BtnEnter[i].SetFont(g_hFontBold);
        m_BtnEnter[i].ChangeText(tierLabels[i]);
    }
}

void CNewUIEnterDevilSquare::ClosingProcess()
{
    SocketClient->ToGameServer()->SendCloseNpcRequest();
}

void CNewUIEnterDevilSquare::LoadImages()
{
    LoadBitmap(L"Interface\\newui_msgbox_back.jpg", IMAGE_ENTERDS_BASE_WINDOW_BACK, GL_LINEAR);
    LoadBitmap(L"Interface\\newui_item_back01.tga", IMAGE_ENTERDS_BASE_WINDOW_TOP, GL_LINEAR);
    LoadBitmap(L"Interface\\newui_item_back02-L.tga", IMAGE_ENTERDS_BASE_WINDOW_LEFT, GL_LINEAR);
    LoadBitmap(L"Interface\\newui_item_back02-R.tga", IMAGE_ENTERDS_BASE_WINDOW_RIGHT, GL_LINEAR);
    LoadBitmap(L"Interface\\newui_item_back03.tga", IMAGE_ENTERDS_BASE_WINDOW_BOTTOM, GL_LINEAR);
    LoadBitmap(L"Interface\\newui_exit_00.tga", IMAGE_ENTERDS_BASE_WINDOW_BTN_EXIT, GL_LINEAR);				// Exit Button
    LoadBitmap(L"Interface\\newui_btn_empty_big.tga", IMAGE_ENTERDS_BASE_WINDOW_BTN_ENTER, GL_LINEAR);		// Enter Button
}

//---------------------------------------------------------------------------------------------
// UnloadImages
void CNewUIEnterDevilSquare::UnloadImages()
{
    DeleteBitmap(IMAGE_ENTERDS_BASE_WINDOW_BACK);
    DeleteBitmap(IMAGE_ENTERDS_BASE_WINDOW_TOP);
    DeleteBitmap(IMAGE_ENTERDS_BASE_WINDOW_LEFT);
    DeleteBitmap(IMAGE_ENTERDS_BASE_WINDOW_RIGHT);
    DeleteBitmap(IMAGE_ENTERDS_BASE_WINDOW_BOTTOM);
    DeleteBitmap(IMAGE_ENTERDS_BASE_WINDOW_BTN_EXIT);		// Exit Button
    DeleteBitmap(IMAGE_ENTERDS_BASE_WINDOW_BTN_ENTER);	// Enter Button
}