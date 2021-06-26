#include "route_planner.h"
#include <algorithm>

RoutePlanner::RoutePlanner(RouteModel &model, float start_x, float start_y, float end_x, float end_y): m_Model(model) {
    // Convert inputs to percentage:
    start_x *= 0.01;
    start_y *= 0.01;
    end_x *= 0.01;
    end_y *= 0.01;

   
    // Storing the nodes in the RoutePlanner's start_node and end_node attributes.
  
  start_node = &m_Model.FindClosestNode(start_x, start_y);
  end_node = &m_Model.FindClosestNode(end_x, end_y);

}


// Implemention the CalculateHValue method.
float RoutePlanner::CalculateHValue(RouteModel::Node const *node) {
     return node->distance(*end_node);
}


// AddNeighbors method to expand the current node by adding all unvisited neighbors to the open list.

void RoutePlanner::AddNeighbors(RouteModel::Node *current_node) {
     
  current_node->FindNeighbors();
  for(auto node: current_node->neighbors){
    node->h_value = CalculateHValue(node);
    node->g_value = current_node->g_value + node->distance(*current_node);
    node->parent = current_node;
    node->visited = true;
    open_list.emplace_back(node);
    }
}
  



// NextNode method to sort the open list and to return the next node.

RouteModel::Node *RoutePlanner::NextNode() {
  
std::sort(std::begin(open_list), std::end(open_list), [](RouteModel::Node* a, RouteModel::Node* b){return (a->h_value + a->g_value) > (b->h_value + b->g_value);});
RouteModel::Node* lstsum = open_list.back();
open_list.pop_back();  
return lstsum;    
}


// ConstructFinalPath method to return the final path found from your A* search.

std::vector<RouteModel::Node> RoutePlanner::ConstructFinalPath(RouteModel::Node *current_node) {
    // Create path_found vector
    distance = 0.0f;
    std::vector<RouteModel::Node> path_found;
    
  //Searching until the parent node is found
    while(current_node->parent != nullptr)
    {
      distance += current_node->distance(*current_node->parent);
      path_found.emplace_back(*current_node);
      current_node = current_node->parent;
    } 
    path_found.emplace_back(*start_node);
    std::reverse(path_found.begin(), path_found.end());
    distance *= m_Model.MetricScale(); // Multiply the distance by the scale of the map to get meters.
    return path_found;

}


// The A* Search algorithm implementation

void RoutePlanner::AStarSearch() {
    RouteModel::Node *current_node = nullptr;
    start_node->visited = true;
    AddNeighbors(start_node);
  
    //Searching throught the open list until the goal node is found
    while(open_list.size()>0){
      current_node = NextNode();
      if(current_node->distance(*end_node) == 0)
      {
       m_Model.path = ConstructFinalPath(current_node);
       return;
      }
      AddNeighbors(current_node);
     }   
}