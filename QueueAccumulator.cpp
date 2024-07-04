template<typename Element, typename Add, typename Accum = Element, typename Merge = Add>
struct QueueAccumulator{
    std::stack<pair<Element, Accum>> stack1, stack2;
    Add add;
    Merge merge;
    Accum empty;
    QueueAccumulator(Accum _empty = Accum(), Add _add = Add()) requires (std::is_same_v<Add, Merge>) : empty(_empty), add(_add), merge(_add){ }
    QueueAccumulator(Accum _empty, Add _add = Add(), Merge _merge = Merge()) requires (!std::is_same_v<Add, Merge>) : empty(_empty), add(_add), merge(_merge) { }
    void push(Element val){
        if(stack2.empty()){
            stack2.push({val, add(empty, val)});
        }
        else stack2.push({val, add(stack2.top().second, val)});
    }
    void _shift_stacks(){
        assert(stack1.size() == 0);
        while(!stack2.empty()){
            Element elem = stack2.top().first;
            stack2.pop();
            if(stack1.size() == 0) stack1.push({elem, add(empty, elem)});
            else stack1.push({elem, add(stack1.top().second, elem)});
        }
    }
    void pop(){
        if(stack1.empty()) _shift_stacks();
        stack1.pop();
    }
    Accum accumulate(){
        if(stack1.empty() && stack2.empty()) return empty;
        if(stack1.empty()) return stack2.top().second;
        if(stack2.empty()) return stack1.top().second;
        return merge(stack1.top().second, stack2.top().second);
        return 0;
    }
    int32_t size(){
        return stack1.size() + stack2.size();
    }
};
