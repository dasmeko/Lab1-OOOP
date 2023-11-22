#pragma once

#include <iostream>
#include <functional>
#include <vector>

using namespace std;

template<typename T>
struct YaleFormat {
	vector<T> values;
	vector<int> colIndeces;
	vector<int> rowDividers;

	YaleFormat<T>() {}
};

template<typename T>
class Matrix {
private:
	int rowSize;
	int colSize;
	bool hasYaleFormat;
	vector<vector<pair<int, T>>> dataLIL;
	YaleFormat<T> dataYale;
public:
	Matrix(const int& m, const int& n) {
		hasYaleFormat = false;
		rowSize = m;
		colSize = n;
		dataLIL = vector<vector<pair<int, T>>>(m, vector<pair<int, T>>());
		dataYale = YaleFormat<T>();
	}

	void setValue(const int& i, const int& j, const T& val) {
		if (i < 0 || i >= rowSize || j < 0 || j >= colSize) {
			throw invalid_argument("Indeces out of bounds");
		}

		if (hasYaleFormat) {
			convertFromYale();
		}
		
		vector<pair<int, T>> row = dataLIL[i];
		int k = 0;
		while (k < row.size()) {
			if (row[k].first > j) {
				break;
			}
			k++;
		}

		if (k == row.size()) {
			dataLIL[i].push_back(pair<int, T>(j, val));
		} else {
			dataLIL[i].insert(dataLIL[i].begin() + k, pair<int, T>(j, val));
		}
	}

	T getValue(const int& i, const int& j) {
		if (i < 0 || i >= rowSize || j < 0 || j >= colSize) {
			throw invalid_argument("Indeces out of bounds");
		}

		if (hasYaleFormat) {
			convertFromYale();
		}
		
		for (pair<int, T> p : dataLIL[i]) {
			if (p.first == j) {
				return p.second;
			}
		}

		return 0;
	}

	pair<int, int> findValue(const T& val) {
		if (hasYaleFormat) {
			convertFromYale();
		}

		for (int i = 0; i < rowSize; i++) {
			for (auto p : dataLIL[i]) {
				if (p.second == val) {
					return pair<int, int>(i, p.first);
				}
			}
		}

		return pair<int, int>(-1, -1);
	}

	T findFirstValueByCriteria(function<bool(T)> func) {
		if (hasYaleFormat) {
			for (auto v : dataYale.values) {
				if (func(v)) {
					return v;
				}
			}
		} else {
			for (auto row : dataLIL) {
				for (auto p : row) {
					if (func(p.second)) {
						return p.second;
					}
				}
			}
		}

		throw invalid_argument("No elements pass the criteria");
	}

	Matrix<T> operator+(Matrix<T> other) {
		if (rowSize != other.rowSize || colSize != other.colSize) {
			throw invalid_argument("Incompatible matrices for addition");
		}

		Matrix<T> result(rowSize, colSize);
		convertFromYale();

		bool converted = false;
		if (other.hasYaleFormat) {
			other.convertFromYale();
			converted = true;
		}

		for (int i = 0; i < rowSize; i++) {
			vector<pair<int, T>> sRow = dataLIL[i], oRow = other.dataLIL[i];
			int x = 0, y = 0;
			
			for (int j = 0; j < colSize; j++) {
				pair<int, T> a = (x < sRow.size()) ? sRow[x] : pair<int, T>(-1, -1);
				pair<int, T> b = (y < oRow.size()) ? oRow[y] : pair<int, T>(-1, -1);
				
				if (a.first == j) {
					if (b.first == j) {
						result.dataLIL[i].push_back(pair<int, T>(j, a.second + b.second));
						x++;
						y++;
					} else {
						result.dataLIL[i].push_back(pair<int, T>(j, a.second));
						x++;
					}
				} else {
					if (b.first == j) {
						result.dataLIL[i].push_back(pair<int, T>(j, b.second));
						y++;
					}
				}
			}
		}

		if (converted) {
			other.convert();
		}

		return result;
	}

	void convert() {
		if (hasYaleFormat) {
			convertFromYale();
		} else {
			convertToYale();
		}
	}

	void display() {
		if (hasYaleFormat) {
			convertFromYale();
		}
		
		for (int i = 0; i < rowSize; i++) {
			int k = 0;

			if (dataLIL[i].size()) {
				for (int j = 0; j < dataLIL[i].size(); j++) {
					while (k < dataLIL[i][j].first) {
						cout << 0 << '\t';
						k++;
					}

					cout << dataLIL[i][j].second << '\t';
					k++;
				}

				while (k < colSize) {
					cout << 0 << '\t';
					k++;
				}
			}
			else {
				for (int j = 0; j < colSize; j++) {
					cout << 0 << '\t';
				}
			}

			cout << '\n';
		}
	}

private:
	void convertToYale() {
		if (!hasYaleFormat) {
			hasYaleFormat = true;

			int k = 0;
			for (int i = 0; i < rowSize; i++) {
				dataYale.rowDividers.push_back(k);

				for (auto p : dataLIL[i]) {
					dataYale.colIndeces.push_back(p.first);
					dataYale.values.push_back(p.second);
					k++;
				}
			}

			dataYale.rowDividers.push_back(k);

			dataLIL = vector<vector<pair<int, T>>>(rowSize, vector<pair<int, T>>());
		}
	}

	void convertFromYale() {
		if (hasYaleFormat) {
			hasYaleFormat = false;

			for (int i = 0; i < rowSize; i++) {
				for (int j = dataYale.rowDividers[i]; j < dataYale.rowDividers[i + 1]; j++) {
					dataLIL[i].push_back(pair<int, T>(dataYale.colIndeces[j], dataYale.values[j]));
				}
			}

			dataYale = YaleFormat<T>();
		}
	}
};