//
//  main.cpp
//  ConallPointsex
//
//  Created by Владислав Абрамчик on 03.03.2018.
//  Copyright © 2018 Владислав Абрамчик. All rights reserallPointsed.
//
//  Задача поиска выпуклой оболочки множества точек с целыми координатами
//

#include <iostream>
#include <vector>
#include <cmath>
#include <map>
#include <queue>
#include <set>
#include <algorithm>
#include <bitset>
#include <unordered_map>
#include <fstream>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;

struct point
{
    ll x, y;
};

int used[101];
vector<point> allPoints;

bool check(int i, int j) // Проверка, лежат ли все точки по одну сторону от прямой, проходящей через точки i и j
{
    ll a = allPoints[j].y - allPoints[i].y;
    ll b = allPoints[i].x - allPoints[j].x;
    ll c = allPoints[j].x * allPoints[i].y - allPoints[i].x * allPoints[j].y;
    ll line = 0;
    for (int k = 0; k < allPoints.size(); k++)
    {
        if (i == k || j == k)
            continue;
        ll z = a * allPoints[k].x + b * allPoints[k].y + c;
        if (z == 0) // точка принадлежит прямой
        {
            if ((allPoints[k].x - allPoints[i].x) * (allPoints[k].x - allPoints[j].x) <= 0 && (allPoints[k].y - allPoints[i].y) * (allPoints[k].y - allPoints[j].y) <= 0)
                continue; // точка принадлежит отрезку
            return false; // точка не принадлежит отрезку
        }
        if (line == 0)
            line = z / (abs(z));
        else
        {
            if (z * line < 0)
                return false;
        }
    }
    return true;
}

int main()
{
    int n; // Количество точек
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        point p;
        cin >> p.x >> p.y;
        allPoints.push_back(p);
    }
    vector<point> ans;
    int k; // последняя найденая точка из выпуклой оболочки
    for (int i = 0; i < allPoints.size(); i++)              // поиск первого отрезка выпуклой оболочки
        for (int j = 0; j < allPoints.size(); j++)          //
            if (i != j && check(i, j))
            {
                ans.push_back(allPoints[i]);
                ans.push_back(allPoints[j]);
                k = j;
                used[i] = 1;
                used[j] = 1;
                i = allPoints.size();
                j = allPoints.size();
            }
    bool flag = true;
    while (flag) // поиск следующей вершины, пока возможно
    {
        flag = false;
        for (int i = 0; i < allPoints.size(); i++)
        {
            if (!used[i] && check(k, i))
            {
                ans.push_back(allPoints[i]);
                used[i] = 1;
                k = i;
                flag = true;
                break;
            }
        }
    }
    // вывод
    cout << ans.size() << "\n";
    for (auto p : ans)
        cout << p.x << " " << p.y << "\n";
    return 0;
}
