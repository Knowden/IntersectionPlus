#include <iostream>
#include <fstream>
#include "Solution.h"

using namespace std;

vector<string> read_input_file(string input_file_path) {
	vector<string> components; // 先存于vector中，一次性IO会更快一些

	ifstream in(input_file_path);
	string component_str;
	getline(in, component_str); // 跳过第一行的数字不要
	while (getline(in, component_str)) {
		components.push_back(component_str);
	}
	in.close();

	return components;
}

void write_result_to_output_file(string output_file_path, int result) {
	ofstream out(output_file_path);
	out << result;
	out.close();
}

int main(int argc, const char** argv) {
	Solution s;
	string input_file_path = string(argv[2]);
	string output_file_path = string(argv[4]);

	vector<string> components = read_input_file(input_file_path);
	for (string component : components) {
		s.add_component(component);
	}

	write_result_to_output_file(output_file_path, s.count_result());
}