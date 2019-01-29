// Copyright (c) 2016 dacci.org

#include "ui/main_dialog.h"

#include <algorithm>

#include "app/application.h"

MainDialog::MainDialog() {}

bool MainDialog::GetAddress(DWORD* address) const {
  if (address == nullptr)
    return false;

  if (ip_address_radio_.GetCheck() & BST_CHECKED) {
    if (ip_address_.GetAddress(address) != 4)
      return false;
  } else if (hex_radio_.GetCheck() & BST_CHECKED) {
    CString value;
    hex_.GetWindowText(value);
    if (value.IsEmpty())
      return false;

    if (swscanf_s(value, L"%x", address) != 1)
      return false;
  } else if (decimal_radio_.GetCheck() & BST_CHECKED) {
    CString value;
    decimal_.GetWindowText(value);
    if (value.IsEmpty())
      return false;

    if (swscanf_s(value, L"%u", address) != 1)
      return false;
  }

  return true;
}

bool MainDialog::GetNetmask(DWORD* netmask) const {
  if (netmask == nullptr)
    return false;

  if (netmask_radio_.GetCheck() & BST_CHECKED) {
    DWORD mask;
    if (netmask_.GetAddress(&mask) != 4)
      return false;

    DWORD forward;
    if (!BitScanForward(&forward, mask))
      return false;

    DWORD reverse;
    if (!BitScanReverse(&reverse, ~mask))
      return false;

    if (forward - reverse != 1)
      return false;

    *netmask = mask;
  } else if (prefix_radio_.GetCheck() & BST_CHECKED) {
    CString value;
    prefix_.GetWindowText(value);
    if (value.IsEmpty())
      return false;

    int length;
    if (swscanf_s(value, L"%u", &length) != 1)
      return false;

    if (length < 0 || 32 < length)
      return false;

    if (length == 32)
      *netmask = MAXDWORD;
    else if (length == 0)
      *netmask = 0;
    else
      *netmask = MAXDWORD << (32 - length);
  } else if (hosts_radio_.GetCheck() & BST_CHECKED) {
    CString value;
    hosts_.GetWindowText(value);
    if (value.IsEmpty())
      return false;

    int hosts;
    if (swscanf_s(value, L"%u", &hosts) != 1)
      return false;

    auto bits = log2(hosts + 2);
    if (!isfinite(bits) || bits > 32)
      return false;

    *netmask = MAXDWORD << static_cast<int>(ceil(bits));
  }

  return true;
}

BOOL MainDialog::PreTranslateMessage(MSG* message) {
  if (IsDialogMessage(message))
    return TRUE;

  return FALSE;
}

BOOL MainDialog::OnInitDialog(CWindow /*focus*/, LPARAM /*init_param*/) {
  DoDataExchange(DDX_LOAD);

  prefix_spin_.SetRange(0, 32);

  ip_address_radio_.SetCheck(BST_CHECKED);
  OnAddressMode(0, IDC_IPADDRESS_RADIO, ip_address_radio_);

  netmask_radio_.SetCheck(BST_CHECKED);
  OnRangeMode(0, IDC_NETMASK_RADIO, netmask_radio_);

  ip_address_.SetFocus(0);

  _Module.GetMessageLoop()->AddMessageFilter(this);

  return FALSE;
}

void MainDialog::OnDestroy() {
  _Module.GetMessageLoop()->RemoveMessageFilter(this);

  PostQuitMessage(0);
}

void MainDialog::OnOK(UINT /*notify_code*/, int /*id*/, CWindow /*control*/) {
  DWORD address;
  if (!GetAddress(&address))
    return;

  DWORD netmask;
  if (!GetNetmask(&netmask))
    return;

  CString value;

  ip_address_.SetAddress(address);

  value.Format(L"%08X", address);
  hex_.SetWindowText(value);

  value.Format(L"%u", address);
  decimal_.SetWindowText(value);

  netmask_.SetAddress(netmask);

  DWORD length;
  if (!BitScanForward(&length, netmask))
    length = 32;

  value.Format(L"%u", 32 - length);
  prefix_.SetWindowText(value);

  value.Format(L"%.f", std::max(pow(2, length) - 2.0, 0.0));
  hosts_.SetWindowText(value);

  network_.SetAddress(address & netmask);
  broadcast_.SetAddress(address | MAXDWORD & ~netmask);
}

void MainDialog::OnCancel(UINT /*notify_code*/, int /*id*/,
                          CWindow /*control*/) {
  DestroyWindow();
}

void MainDialog::OnAbort(UINT /*notify_code*/, int /*id*/,
                         CWindow /*control*/) {
  ip_address_.ClearAddress();
  hex_.Clear();
  decimal_.Clear();
  netmask_.ClearAddress();
  prefix_.Clear();
  hosts_.Clear();
  network_.ClearAddress();
  broadcast_.ClearAddress();
}

void MainDialog::OnAddressMode(UINT /*notify_code*/, int id,
                               CWindow /*control*/) {
  ip_address_.EnableWindow(FALSE);
  hex_.EnableWindow(FALSE);
  decimal_.EnableWindow(FALSE);

  switch (id) {
    case IDC_IPADDRESS_RADIO:
      ip_address_.EnableWindow();
      ip_address_.SetFocus(0);
      break;

    case IDC_HEX_RADIO:
      hex_.EnableWindow();
      hex_.SetFocus();
      break;

    case IDC_DECIMAL_RADIO:
      decimal_.EnableWindow();
      decimal_.SetFocus();
      break;
  }
}

void MainDialog::OnRangeMode(UINT /*notify_code*/, int id,
                             CWindow /*control*/) {
  netmask_.EnableWindow(FALSE);
  prefix_.EnableWindow(FALSE);
  hosts_.EnableWindow(FALSE);

  switch (id) {
    case IDC_NETMASK_RADIO:
      netmask_.EnableWindow();
      netmask_.SetFocus(0);
      break;

    case IDC_PREFIX_RADIO:
      prefix_.EnableWindow();
      prefix_.SetFocus();
      break;

    case IDC_HOSTS_RADIO:
      hosts_.EnableWindow();
      hosts_.SetFocus();
      break;
  }
}
