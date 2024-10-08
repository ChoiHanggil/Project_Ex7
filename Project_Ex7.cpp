﻿#include <iostream>
#include<vector>
#include<queue>
#include <unordered_set>
#include<string>
#include <sstream>
#include <stack>
#include <unordered_map>

struct ListNode
{
	int val;
	ListNode* next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode* next) : val(x), next(next) {}
};

//1.
ListNode* MergeTwoList(ListNode* list1, ListNode* list2)
{
	auto p1 = list1;
	auto p2 = list2;

	ListNode* temp = new ListNode();
	auto head = temp;

	while (p1 != nullptr && p2 != nullptr)
	{
		if (p1->val < p2->val )
		{
			temp->next = p1;
			p1 = p1->next;
		}else
		{
			temp->next = p2;
			p2 = p2->next;
		}
		temp = temp->next;
	}

	if (p1 == nullptr)
	{
		temp->next = p2;
	}
	else
	{
		temp->next = p1;
	}
	
	return head->next;
}

//2.
//int CountComponents(int n, std::vector<std::vector<int>>& edges)
//{
//	for (auto& e : edges)
//	{
//		if (e[0] > e[1])
//		{
//			std::swap(e[0], e[1]);
//		}
//	}
//
//	std::sort(edges.begin(), edges.end());
//
//	int count{ 1 };
//	int temp = edges[0][1];
//	for (int i = 1; i < edges.size(); i++)
//	{
//		if (temp != edges[i][0])
//		{
//			count++;
//		}
//
//		temp = edges[i][1];
//	}
//
//	return count;
//}

void BFS(int search, std::vector<std::vector<int>>& adjList, std::unordered_set<int>& record) 
{
	std::queue<int> q;
	q.push(search);
	record.insert(search);

	while (!q.empty()) 
	{
		int node = q.front();
		q.pop();

		for (int neighbor : adjList[node]) 
		{
			if (record.find(neighbor) == record.end()) 
			{
				record.insert(neighbor);
				q.push(neighbor);
			}
		}
	}
}

int CountComponents(int n, std::vector<std::vector<int>>& edges) 
{
	std::vector<std::vector<int>> adjList(n);//adjecebcy list
	for (const auto& edge : edges) 
	{
		adjList[edge[0]].push_back(edge[1]);
		adjList[edge[1]].push_back(edge[0]);
	}

	std::unordered_set<int> record;
	int count = 0;

	for (int i = 0; i < n; i++) 
	{
		if (record.find(i) == record.end()) 
		{
			BFS(i, adjList, record);
			count++;
		}
	}

	return count;
}
void DFS(int node, std::vector<std::vector<int>>& adjList, std::vector<bool>& visited)
{
	visited[node] = true;
	for (const auto& neighbor : adjList[node])
	{
		if (!visited[neighbor])
		{
			DFS(neighbor, adjList, visited);
		}
	}
}
int CountComponents3(int n, std::vector<std::vector<int>>& edges)
{
	//adjacency list
	std::vector<std::vector<int>> adjList(n);
	for (const auto& edge  : edges)
	{
		int u = edge[0];
		int v = edge[1];

		adjList[u].push_back(v);
		adjList[v].push_back(u);
	}

	std::vector<bool> visited(n, false);
	int count{};

	for (int i = 0; i < n; i++)
	{
		if (!visited[i])
		{
			DFS(i, adjList, visited);
			count++;
		}
	}
}



struct TreeNode
{
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};
//3.
class Codec
{
public:
	std::string Serialize(TreeNode* root)
	{
		std::string s;
		if (root == nullptr)
		{
			return "";
		}
		std::queue<TreeNode*> q;
		q.push(root);

		while (!q.empty())
		{
			auto node = q.front();

			q.pop();
			if (node != nullptr)
			{
				s += std::to_string(node->val) + ',';
				q.push(node->left);
				q.push(node->right);
			}else
			{
				s += "N,";
			}
		}

		return s;
	}

	TreeNode* Deserialize(std::string data)
	{
		std::istringstream iss(data);
		std::string c;
		std::getline(iss, c, ',');

		TreeNode* root = new TreeNode(std::stoi(c));

		std::queue<TreeNode*> q;

		q.push(root);

		while (!q.empty())
		{
			auto node = q.front();
			q.pop();

			std::getline(iss, c, ',');
			if (c != "N")
			{
				auto left = new TreeNode(std::stoi(c));
				node->left = left;
				q.push(left);
			}

			std::getline(iss, c, ',');
			if (c != "N")
			{
				auto right = new TreeNode(std::stoi(c));
				node->right = right;
				q.push(right);
			}
		}

		return root;
	}
};

//4.
std::vector<int> TwoSum2(std::vector<int>& nums, int target) {
	std::unordered_map<int, int> umap;
	for (int i = 0; i < nums.size(); ++i) 
	{
		int complement = target - nums[i];
		if (umap.find(complement) != umap.end()) 
		{
			return { umap[complement], i };
		}
		umap[nums[i]] = i;
	}
	return {};
}


std::vector<int> TwoSum(std::vector<int>& nums, int target)
{
	std::vector<int> ans;
	int j;
	for (int i = 0; i < nums.size(); i++)
	{
		for (j = i + 1; j < nums.size(); j++);
		{
			if (nums[i] + nums[j] == target)
			{
				ans.push_back(i);
				ans.push_back(j);
			}
		}
	}
	return ans;
}

//5.
TreeNode* InverBT(TreeNode* root)
{
	std::queue<TreeNode*> q;
	q.push(root);

	TreeNode* temp = nullptr;

	while (!q.empty())
	{
		auto node = q.front();
		q.pop();

		if (node->left) 
		{ 
			q.push(node->left); 	
			temp = node->left;
			node->left = node->right;
		}
		if (node->right) 
		{ 
			q.push(node->right); 
			node->right = temp;
		}

	}

	return root;
}



void PrintTree(TreeNode* root) {
	if (!root) return;
	std::queue<TreeNode*> q;
	q.push(root);
	while (!q.empty()) {
		TreeNode* node = q.front();
		q.pop();
		std::cout << node->val << " ";
		if (node->left) q.push(node->left);
		if (node->right) q.push(node->right);
	}
}
void PrintList(ListNode* head) {
	while (head != nullptr) {
		std::cout << head->val << " ";
		head = head->next;
	}
	std::cout << std::endl;
}

int main()
{

	//// 첫 번째 리스트: 1 -> 3 -> 5
	//ListNode* list1 = new ListNode(1, new ListNode(3, new ListNode(5)));

	//// 두 번째 리스트: 2 -> 4 -> 6
	//ListNode* list2 = new ListNode(2, new ListNode(4, new ListNode(6)));

	//ListNode* mergedList = MergeTwoList(list1, list2);

	//std::cout << "Merged List: ";
	//PrintList(mergedList);


	//int n = 5; // 노드의 수
	//std::vector<std::vector<int>> edges = {
	//	{0,1},{1,2},{3,4}, { 4,0 }
	//};

	//int numComponents = CountComponents(n, edges);
	//std::cout << "Number of connected components: " << numComponents << std::endl;


	//TreeNode* root = new TreeNode(1);
	//root->left = new TreeNode(2);
	//root->right = new TreeNode(3);
	//root->right->left = new TreeNode(4);
	//root->right->right = new TreeNode(5);

	//Codec ser, deser;
	//TreeNode* ans = deser.Deserialize(ser.Serialize(root)) ;

	//std::cout << ser.Serialize(root) << std::endl;
	//PrintTree(ans);


	//TreeNode* root = new TreeNode(1);
	//root->left = new TreeNode(2);
	//root->right = new TreeNode(3);
	//root->left->left = new TreeNode(4);
	//root->left->right = new TreeNode(5);
	//root->right->left = new TreeNode(6);
	//root->right->right = new TreeNode(7);

	//std::cout << "Original Tree: ";
	//PrintTree(root);
	//std::cout << std::endl;

	//TreeNode* invertedRoot = InverBT(root);

	//std::cout << "Inverted Tree: ";
	//PrintTree(invertedRoot);
	//std::cout << std::endl;


	//std::vector<int> nums{ 3,2,4 };
	//for (auto e : TwoSum2(nums, 6))
	//{
	//	std::cout << e;
	//}

}

