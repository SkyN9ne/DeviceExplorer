#pragma once

#include "VirtualListView.h"
#include "DeviceManager.h"
#include "ViewBase.h"

class DeviceNode;

class CDevNodeListView :
	public CFrameWindowImpl<CDevNodeListView, CWindow, CControlWinTraits>,
	public CViewBase<CDevNodeListView>,
	public CVirtualListView<CDevNodeListView> {
public:
	using CViewBase::CViewBase;
	using BaseFrame = CFrameWindowImpl<CDevNodeListView, CWindow, CControlWinTraits>;
	DECLARE_WND_CLASS(nullptr)

	void Refresh();

protected:
	BEGIN_MSG_MAP(CDevNodeListView)
		MESSAGE_HANDLER(WM_SETFOCUS, OnSetFocus)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		CHAIN_MSG_MAP(CVirtualListView<CDevNodeListView>)
		CHAIN_MSG_MAP(BaseFrame)
	END_MSG_MAP()

	CString GetColumnText(HWND, int row, int col);
	int GetRowImage(HWND, int row, int col);
	void DoSort(SortInfo* const si);

	// Handler prototypes (uncomment arguments if needed):
//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

	enum class ColumnType {
		Name, Class, ClassGuid,
		Status, Instance, Driver, Enumerator, PDOName, Parent,
	};

private:
	struct DeviceItem : DeviceInfo {
		CString Class;
		int Image{ -1 };
	};

	CString const& GetDeviceClassName(DeviceItem& di);
	CString GetStringProperty(DeviceItem& item, DEVPROPKEY const& key);

	LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnSetFocus(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);

	CListViewCtrl m_List;
	std::vector<DeviceItem> m_Items;
	std::unique_ptr<DeviceManager> m_dm;
};