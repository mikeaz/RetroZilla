/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is mozilla.org code.
 *
 * The Initial Developer of the Original Code is
 * Netscape Communications Corporation.
 * Portions created by the Initial Developer are Copyright (C) 1998
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either of the GNU General Public License Version 2 or later (the "GPL"),
 * or the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the MPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the MPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */

#ifndef nsPluginArray_h___
#define nsPluginArray_h___

#include "nsIDOMPluginArray.h"
#include "nsIDOMPlugin.h"
#include "nsIPluginHost.h"
#include "nsIURL.h"

class nsNavigator;
class nsIDocShell;
class nsIPluginHost;

// NB: Due to weak references, nsNavigator has intimate knowledge of our
// internals.
class nsPluginArray : public nsIDOMPluginArray,
                      public nsIDOMJSPluginArray
{
public:
  nsPluginArray(nsNavigator* navigator, nsIDocShell *aDocShell);
  virtual ~nsPluginArray();

  NS_DECL_ISUPPORTS

  // nsIDOMPluginArray
  NS_DECL_NSIDOMPLUGINARRAY

  // nsIDOMJSPluginArray
  NS_DECL_NSIDOMJSPLUGINARRAY

  nsresult GetPluginHost(nsIPluginHost** aPluginHost);

private:
  nsresult GetPlugins();
  PRBool AllowPlugins();

public:
  void SetDocShell(nsIDocShell *aDocShell);
  void Invalidate();

protected:
  nsNavigator* mNavigator;
  nsCOMPtr<nsIPluginHost> mPluginHost;
  PRUint32 mPluginCount;
  nsIDOMPlugin** mPluginArray;
  nsIDocShell* mDocShell; // weak reference
};

class nsPluginElement : public nsIDOMPlugin
{
public:
  nsPluginElement(nsIDOMPlugin* plugin);
  virtual ~nsPluginElement();

  NS_DECL_ISUPPORTS

  NS_IMETHOD GetDescription(nsAString& aDescription);
  NS_IMETHOD GetFilename(nsAString& aFilename);
  NS_IMETHOD GetName(nsAString& aName);
  NS_IMETHOD GetLength(PRUint32* aLength);
  NS_IMETHOD Item(PRUint32 aIndex, nsIDOMMimeType** aReturn);
  NS_IMETHOD NamedItem(const nsAString& aName, nsIDOMMimeType** aReturn);

private:
  nsresult GetMimeTypes();

protected:
  nsIDOMPlugin* mPlugin;
  PRUint32 mMimeTypeCount;
  nsIDOMMimeType** mMimeTypeArray;
};

#endif /* nsPluginArray_h___ */
