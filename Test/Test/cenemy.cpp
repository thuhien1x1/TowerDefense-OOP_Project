#include "cenemy.h"
#include <queue>
#include <vector>
#include <algorithm>

cenemy::cenemy() {
    for (int i = 0; i < cpoint::MAP_ROW * cpoint::MAP_COL; i++)
        _p[i] = cpoint();
    dd[0] = -1; dd[1] = 0; dd[2] = 1; dd[3] = 0;
    dc[0] = 0; dc[1] = -1; dc[2] = 0; dc[3] = 1;
    _start = _end = _curr = cpoint();
    _speed = 3;
    _pathLength = 0;
}

cenemy::cenemy(cpoint tstart, cpoint tend, cpoint tcurr) : cenemy() {
    _start = tstart;
    _end = tend;
    _curr = tcurr;
}

void cenemy::setSpeed(int tspeed) { if (tspeed > 0 && tspeed < 10) _speed = tspeed; }
void cenemy::setStart(const cpoint& tstart) { _start = tstart; }
void cenemy::setEnd(const cpoint& tend) { _end = tend; }
void cenemy::setCurr(const cpoint& tcurr) { _curr = tcurr; }

void cenemy::calcPath(int a[][cpoint::MAP_COL], int n, cpoint s, cpoint e) {
    std::queue<cpoint> q;
    bool visited[cpoint::MAP_ROW][cpoint::MAP_COL] = {};
    cpoint parent[cpoint::MAP_ROW][cpoint::MAP_COL];

    q.push(s);
    visited[s.getRow()][s.getCol()] = true;
    parent[s.getRow()][s.getCol()] = s;

    bool found = false;
    while (!q.empty()) {
        cpoint curr = q.front(); q.pop();
        if (curr.getRow() == e.getRow() && curr.getCol() == e.getCol()) {
            found = true;
            break;
        }
        for (int i = 0; i < 4; i++) {
            int dmoi = dd[i] + curr.getRow(), cmoi = dc[i] + curr.getCol();
            if (dmoi >= 0 && dmoi < cpoint::MAP_ROW && cmoi >= 0 && cmoi < cpoint::MAP_COL
                && !visited[dmoi][cmoi] && a[dmoi][cmoi] == 0) {
                visited[dmoi][cmoi] = true;
                parent[dmoi][cmoi] = curr;
                q.push(cpoint(dmoi, cmoi, 0));
            }
        }
    }

    if (found) {
        std::vector<cpoint> pathList;
        cpoint curr = e;
        while (!(curr.getRow() == s.getRow() && curr.getCol() == s.getCol())) {
            pathList.push_back(curr);
            curr = parent[curr.getRow()][curr.getCol()];
        }
        pathList.push_back(s);
        std::reverse(pathList.begin(), pathList.end());
        int i = 0;
        for (auto& p : pathList) _p[i++] = p;
        _pathLength = i;
    }
    else {
        _pathLength = 0;
    }
}

void cenemy::findPath(cpoint a[][cpoint::MAP_COL], cpoint s, cpoint e) {
    int ta[cpoint::MAP_ROW][cpoint::MAP_COL];
    for (int i = 0; i < cpoint::MAP_ROW; i++)
        for (int j = 0; j < cpoint::MAP_COL; j++)
            ta[i][j] = a[i][j].getC();
    calcPath(ta, cpoint::MAP_ROW, s, e);
}
