#include "MapViewer.h"

void MapViewer::DisplayMap(const vector<vector<int>>& map) const
{
	for (auto nxt : map)
	{
		for (auto nxt1 : nxt)
		{
			if (nxt1 == 1)
				cout << "бс";
			else if (nxt1 == 2)
				cout << "бу";
			else if (nxt1 == 0)
				cout << "  ";
		}
		cout << "\n";
	}
	cout << endl;
}

void MapViewer::Rendering() const
{
	for (auto vec : renderedMap)
	{
		for (auto iter : vec)
			cout << iter;
	}
	cout << endl;
}

void MapViewer::SetRenderedMap(const vector<vector<string>>& map)
{
	renderedMap = map;
}
