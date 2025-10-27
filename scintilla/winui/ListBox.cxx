// Scintilla source code edit control
/** @file ListBox.cxx
 ** Implementation of list box on Windows.
 **/
// Copyright 1998-2003 by Neil Hodgson <neilh@scintilla.org>
// The License.txt file describes the conditions under which this software may be distributed.

#include "pch.h"

#include <cstddef>
#include <cstdlib>
#include <cstdint>
#include <cstring>
#include <cstdio>
#include <cstdarg>
#include <ctime>
#include <cmath>
#include <climits>

#include <string_view>
#include <vector>
#include <map>
#include <optional>
#include <algorithm>
#include <iterator>
#include <memory>
#include <mutex>

// Want to use std::min and std::max so don't want Windows.h version of min and max
#if !defined(NOMINMAX)
#define NOMINMAX
#endif
#undef _WIN32_WINNT
#define _WIN32_WINNT 0x0A00
#undef WINVER
#define WINVER 0x0A00
#define WIN32_LEAN_AND_MEAN 1
#include <windows.h>
#include <commctrl.h>
#include <richedit.h>
#include <windowsx.h>
#include <shellscalingapi.h>

#if !defined(DISABLE_D2D)
#define USE_D2D 1
#endif

#if defined(USE_D2D)
#include <d2d1_1.h>
#include <d3d11_1.h>
#include <dwrite_1.h>
#endif

#include "ScintillaTypes.h"

#include "Debugging.h"
#include "Geometry.h"
#include "Platform.h"
#include "XPM.h"
#include "UniConversion.h"
#include "DBCS.h"

#include "WinTypes.h"
#include "PlatWin.h"
#include "ListBox.h"
#if defined(USE_D2D)
#include "SurfaceD2D.h"
#endif

using namespace Scintilla;
using namespace Scintilla::Internal;

namespace {

struct ListItemData {
	const char *text;
	int pixId;
};

class LineToItem {
	std::vector<char> words;

	std::vector<ListItemData> data;

public:
	void Clear() noexcept {
		words.clear();
		data.clear();
	}

	[[nodiscard]] ListItemData Get(size_t index) const noexcept {
		if (index < data.size()) {
			return data[index];
		}
		ListItemData missing = {"", -1};
		return missing;
	}
	[[nodiscard]] int Count() const noexcept {
		return static_cast<int>(data.size());
	}

	void AllocItem(const char *text, int pixId) {
		const ListItemData lid = { text, pixId };
		data.push_back(lid);
	}

	char *SetWords(const char *s) {
		words = std::vector<char>(s, s+strlen(s)+1);
		return words.data();
	}
};

}

class ListBoxWinUI : public ListBox {
	public:
	ListBoxWinUI() noexcept;
	virtual ~ListBoxWinUI() noexcept override;

	virtual void SetFont(const Font *font);
	virtual void Create(Window &parent, int ctrlID, Point location, int lineHeight_, bool unicodeMode_, Scintilla::Technology technology_);
	virtual void SetAverageCharWidth(int width);
	virtual void SetVisibleRows(int rows);
	virtual int GetVisibleRows() const;
	virtual PRectangle GetDesiredRect();
	virtual int CaretFromEdge();
	virtual void Clear() noexcept;
	virtual void Append(char *s, int type = -1);
	virtual int Length();
	virtual void Select(int n);
	virtual int GetSelection();
	virtual int Find(const char *prefix);
	virtual std::string GetValue(int n);
	virtual void RegisterImage(int type, const char *xpm_data);
	virtual void RegisterRGBAImage(int type, int width, int height, const unsigned char *pixelsImage);
	virtual void ClearRegisteredImages();
	virtual void SetDelegate(IListBoxDelegate *lbDelegate);
	virtual void SetList(const char* list, char separator, char typesep);
	virtual void SetOptions(ListOptions options_);
};

ListBoxWinUI::ListBoxWinUI() noexcept
{
}

ListBoxWinUI::~ListBoxWinUI() noexcept
{
}

void ListBoxWinUI::SetFont(const Font *font)
{

}

void ListBoxWinUI::Create(Window &parent, int ctrlID, Point location, int lineHeight_, bool unicodeMode_, Scintilla::Technology technology_)
{

}

void ListBoxWinUI::SetAverageCharWidth(int width)
{

}

void ListBoxWinUI::SetVisibleRows(int rows)
{

}

int ListBoxWinUI::GetVisibleRows() const
{
	return 0;
}

PRectangle ListBoxWinUI::GetDesiredRect()
{
	return PRectangle{ 0, 0, 10, 10 };
}

int ListBoxWinUI::CaretFromEdge()
{
	return 0;
}

void ListBoxWinUI::Clear() noexcept
{

}

void ListBoxWinUI::Append(char *s, int type)
{

}

int ListBoxWinUI::Length()
{
	return 0;
}

void ListBoxWinUI::Select(int n)
{

}

int ListBoxWinUI::GetSelection()
{
	return 0;
}

int ListBoxWinUI::Find(const char *prefix)
{
	return -1;
}

std::string ListBoxWinUI::GetValue(int n)
{
	return {};
}

void ListBoxWinUI::RegisterImage(int type, const char *xpm_data)
{

}

void ListBoxWinUI::RegisterRGBAImage(int type, int width, int height, const unsigned char *pixelsImage)
{

}

void ListBoxWinUI::ClearRegisteredImages()
{

}

void ListBoxWinUI::SetDelegate(IListBoxDelegate *lbDelegate)
{

}

void ListBoxWinUI::SetList(const char *list, char separator, char typesep)
{

}

void ListBoxWinUI::SetOptions(ListOptions options_)
{

}

std::unique_ptr<ListBox> ListBox::Allocate() {
	return std::make_unique<ListBoxWinUI>();
}

namespace Scintilla::Internal {

ListBox::ListBox() noexcept = default;

ListBox::~ListBox() noexcept = default;

}
