//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <string.h>


#include "Unit1.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

#define INDEX_NOTFOUND (-1)



struct TStudent
{
	bool Active;
	int No;
	char Name[100];
	int Age;
	char Job[100];

	TStudent()
	{
		Clear();
	}
	void Clear()
	{
		ZeroMemory(this, sizeof(*this));
	}

};

class CStudent
{
public:
	TStudent *Data;
	int Size;

public:
	CStudent()
	{
		Data = NULL;
		Size = 0;
	}

	CStudent(int size)
	{
		Data = NULL;
		SetSize(size);
	}

	void SetSize(int size)
	{
		if (Data) delete[] Data;
		Data = new TStudent[size];
		Size = size;
	}

	~CStudent()
	{
		if (Data) delete[] Data;
	}

	int Add(TStudent& data)
	{
		if (!Data)
		{
			return INDEX_NOTFOUND;
		}
		int idx = FindBlank();
		if (idx >= 0)
		{
			Data[idx] = data;
		}
		return idx;
	}

	void Delete(int idx)
	{
		if (!Data)
		{
			return;
		}

		if (idx < Size)
		{
			Data[idx].Clear();
		}
    }

	int FindNo(int No)
	{
		for (int c = 0; c < Size; c++)
		{
			if (Data[c].Active && Data[c].No == No)
			{
				return c;
			}
		}
		return INDEX_NOTFOUND;
	}

	TStudent* Find(int No)
	{
		for (int c = 0; c < Size; c++)
		{
			if (Data[c].Active && Data[c].No == No)
			{
				return Data + c;
			}
		}
		return NULL;
	}

	int FindBlank()
	{
		for (int i = 0; i < Size; i++)
		{
			if (Data[i].Active == false)
			{
				return i;
			}
			return INDEX_NOTFOUND;
        }
	}

	int FindName(String name)
	{
		for (int c = 0; c < Size; c++)
		{
			if (name == Data[c].Name)
			{
				return c;
			}
			return INDEX_NOTFOUND;
		}
	}

	void Load(char* filename)
	{
		TFILE file(filename, "rb");
		if (file.fp == NULL)
		{
			return;
		}
		int filesize = file.GetFileSize();
		SetSize(filesize / sizeof(TStudent));
		file.fread(Data, filesize, 1);
	}

	void Save(char* filename)
	{
		TFILE file(filename, "wb");
		if (file.fp == NULL)
		{
			return;
		}
		file.fwrite(Data, Size * sizeof(TStudent), 1);
	}

};




void __fastcall TForm1::addButtonClick(TObject *Sender)
{
	TStudent st;
	st.No = studentNumber->Text.ToIntDef(0);
	strcpy(st.Name, studentName->Text.c_str());
	st.Age = studentAge->Text.ToIntDef(0);
	st.Active = true;
	if (st.No == 0 || st.Name[0] == 0 || st.Age == 0)
	{
		ShowMessage("제대로 입력하시오.");
		return;
	}

	if (Student.FindNo(st.No) != INDEX_NOTFOUND)
	{
		ShowMessage("이미 있는 학번");
		return;
	}

	if (Student.Add(st) == INDEX_NOTFOUND)
	{
		ShowMessage("overflow");
		return;
	}

	AddStudent(st);
}
//---------------------------------------------------------------------------
CStudent Student(100);
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject* Sender)
{
	Student.Load("Student.dat");
	for (int c = 0; c < Student.Size; c++)
	{
		if (Student.Data[c].Active)
		{
		AddStudent(Student.Data[c]);
		}
	}
}

void __fastcall TForm1::FormClose(TObject* Sender, TCloseAction& Action)
{
	Student.Save("Student.dat");
}




