// Copyright (c) 2016 dacci.org

#ifndef IP_CALC_UI_MAIN_DIALOG_H_
#define IP_CALC_UI_MAIN_DIALOG_H_

#include <atlbase.h>
#include <atlstr.h>
#include <atlwin.h>

#include <atlapp.h>
#include <atlcrack.h>
#include <atlctrls.h>
#include <atlddx.h>

#include "res/resource.h"

class MainDialog : public CDialogImpl<MainDialog>,
                   public CWinDataExchange<MainDialog>,
                   private CMessageFilter {
 public:
  static const UINT IDD = IDD_MAIN;

  MainDialog();

  BEGIN_MSG_MAP(MainDialog)
    MSG_WM_INITDIALOG(OnInitDialog)
    MSG_WM_DESTROY(OnDestroy)

    COMMAND_ID_HANDLER_EX(IDOK, OnOK)
    COMMAND_ID_HANDLER_EX(IDCANCEL, OnCancel)
    COMMAND_ID_HANDLER_EX(IDABORT, OnAbort)

    COMMAND_ID_HANDLER_EX(IDC_IPADDRESS_RADIO, OnAddressMode)
    COMMAND_ID_HANDLER_EX(IDC_HEX_RADIO, OnAddressMode)
    COMMAND_ID_HANDLER_EX(IDC_DECIMAL_RADIO, OnAddressMode)
    COMMAND_ID_HANDLER_EX(IDC_NETMASK_RADIO, OnRangeMode)
    COMMAND_ID_HANDLER_EX(IDC_PREFIX_RADIO, OnRangeMode)
    COMMAND_ID_HANDLER_EX(IDC_HOSTS_RADIO, OnRangeMode)
  END_MSG_MAP()

  BEGIN_DDX_MAP(MainDialog)
    DDX_CONTROL_HANDLE(IDC_IPADDRESS_RADIO, ip_address_radio_)
    DDX_CONTROL_HANDLE(IDC_IPADDRESS, ip_address_)
    DDX_CONTROL_HANDLE(IDC_HEX_RADIO, hex_radio_)
    DDX_CONTROL_HANDLE(IDC_HEX, hex_)
    DDX_CONTROL_HANDLE(IDC_DECIMAL_RADIO, decimal_radio_)
    DDX_CONTROL_HANDLE(IDC_DECIMAL, decimal_)
    DDX_CONTROL_HANDLE(IDC_NETMASK_RADIO, netmask_radio_)
    DDX_CONTROL_HANDLE(IDC_NETMASK, netmask_)
    DDX_CONTROL_HANDLE(IDC_PREFIX_RADIO, prefix_radio_)
    DDX_CONTROL_HANDLE(IDC_PREFIX, prefix_)
    DDX_CONTROL_HANDLE(IDC_PREFIX_SPIN, prefix_spin_)
    DDX_CONTROL_HANDLE(IDC_HOSTS_RADIO, hosts_radio_)
    DDX_CONTROL_HANDLE(IDC_HOSTS, hosts_)
    DDX_CONTROL_HANDLE(IDC_NETWORK, network_)
    DDX_CONTROL_HANDLE(IDC_BROADCAST, broadcast_)
  END_DDX_MAP()

 private:
  bool GetAddress(DWORD* address) const;
  bool GetNetmask(DWORD* netmask) const;

  BOOL PreTranslateMessage(MSG* message) override;

  BOOL OnInitDialog(CWindow focus, LPARAM init_param);
  void OnDestroy();

  void OnOK(UINT notify_code, int id, CWindow control);
  void OnCancel(UINT notify_code, int id, CWindow control);
  void OnAbort(UINT notify_code, int id, CWindow control);

  void OnAddressMode(UINT notify_code, int id, CWindow control);
  void OnRangeMode(UINT notify_code, int id, CWindow control);

  CButton ip_address_radio_;
  CIPAddressCtrl ip_address_;
  CButton hex_radio_;
  CEdit hex_;
  CButton decimal_radio_;
  CEdit decimal_;
  CButton netmask_radio_;
  CIPAddressCtrl netmask_;
  CButton prefix_radio_;
  CEdit prefix_;
  CUpDownCtrl prefix_spin_;
  CButton hosts_radio_;
  CEdit hosts_;
  CIPAddressCtrl network_;
  CIPAddressCtrl broadcast_;

  MainDialog(const MainDialog&) = delete;
  MainDialog& operator=(const MainDialog&) = delete;
};

#endif  // IP_CALC_UI_MAIN_DIALOG_H_
