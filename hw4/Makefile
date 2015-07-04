CC=g++
FNAME=a1a.train
PNAME=a1a.test
EPSILON=0
T=30
RM=rm -rf

.PHONY: clean_tree_pred_func clean_forest_pred_func run_tree run_forest predict_tree predict_forest clean

run_tree: tree run_decision_tree
run_forest: forest run_decision_forest
predict_tree: $(PNAME) tree_predictor.cpp tree_pred_func.cpp
	$(CC) tree_predictor.cpp tree_pred_func.cpp -o tree_predictor
	./tree_predictor $(PNAME) > ./tree_prediction.txt
predict_forest: $(PNAME) forest_predictor.cpp forest_pred_func.cpp
	$(CC) forest_predictor.cpp forest_pred_func.cpp -o forest_predictor
	./forest_predictor $(PNAME) > ./forest_prediction.txt

tree: tree.cpp
	$(CC) tree.cpp -o $@
forest: forest.cpp
	$(CC) forest.cpp -o $@
run_decision_tree:
	./tree $(FNAME) $(EPSILON) > tree_pred_func.cpp
run_decision_forest:
	./forest $(FNAME) $(T) > forest_pred_func.cpp

clean_tree_pred_func: 
	$(RM) tree_pred_func.cpp
clean_forest_pred_func: 
	$(RM) forest_pred_func.cpp

#tree_pred_func.cpp: tree $(FNAME)
#	./tree $(FNAME) $(EPSILON) > $@
                      
#forest_pred_func.cpp: forest $(FNAME)
#	./forest $(FNAME) $(T) > $@

#run_tree: predict_tree clean_tree_pred_func
#run_forest: clean_forest_pred_func predict_forest

clean:
	$(RM) tree_predictor forest_predictor tree_pred_func.cpp forest_pred_func.cpp
