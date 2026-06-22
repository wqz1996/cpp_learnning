class Printer {
private:
	vector<int> res;
public:
	vector<int> arrayPrint(vector<vector<int> > arr, int n) {
		if (arr.empty())
			return res;
		int rowlen = arr.size();
		int collen = arr[0].size();
		int row = 0;
		int col = arr[0].size() - 1;
		int times = 2 * n - 1;
		for (int i = 0; i < times; i++) {
			int tempcol = col;
			int temprow = row;
			while (row < rowlen && col < collen) {
				res.push_back(arr[row++][col++]);
			}
			if (tempcol > 0) {
				row = 0;
				col = tempcol-1;
			}
			else {
				row = temprow + 1;
				col = 0;
			}
		}
		return res;

	}
};