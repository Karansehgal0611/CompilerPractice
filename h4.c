#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STATES 100

// Structure to represent a state in NFA
typedef struct State {
    int state_id;
    int num_transitions;
    char symbols[MAX_STATES];  // Array to store transition symbols
    int next_states[MAX_STATES];  // Array to store corresponding next states for each symbol
} State;

// Function to create a new state
State* create_state(int state_id) {
    State *s = (State*)malloc(sizeof(State));
    s->state_id = state_id;
    s->num_transitions = 0;
    return s;
}

// Function to add a transition to a state
void add_transition(State *s, char symbol, int next_state) {
    s->symbols[s->num_transitions] = symbol;
    s->next_states[s->num_transitions] = next_state;
    s->num_transitions++;
}

// Function to handle concatenation of states
void handle_concatenation(State *s1, State *s2) {
    add_transition(s1, '\0', s2->state_id);  // Epsilon transition for concatenation
}

// Function to convert a regular expression to NFA
State* re_to_nfa(char *re, State *states[], int *state_count) {
    State *start_state = create_state((*state_count)++);
    State *end_state = create_state((*state_count)++);

    states[start_state->state_id] = start_state;
    states[end_state->state_id] = end_state;

    // Stack to store states during parsing
    State *stack[MAX_STATES];
    int stack_top = -1;

    // Stack for parentheses handling
    int open_parenthesis[MAX_STATES];  // Store opening parenthesis indices
    int paren_top = -1;

    for (int i = 0; re[i] != '\0'; i++) {
        switch (re[i]) {
            case '(': {  // Opening parenthesis
                open_parenthesis[++paren_top] = stack_top;  // Save the current stack top index
                break;
            }
            case ')': {  // Closing parenthesis
                int start_idx = open_parenthesis[paren_top--];  // Get the corresponding opening parenthesis
                State *s1 = stack[start_idx];
                State *s2 = stack[stack_top];
                handle_concatenation(s1, s2);  // Concatenate states inside parentheses
                stack[stack_top = start_idx] = s1;
                break;
            }
            case '|': {  // Union
                stack_top--;
                State *s2 = stack[stack_top];
                State *s1 = stack[stack_top - 1];
                State *new_s = create_state((*state_count)++);
                states[new_s->state_id] = new_s;
                add_transition(new_s, '\0', s1->state_id);
                add_transition(new_s, '\0', s2->state_id);
                stack[stack_top - 1] = new_s;
                stack_top--;
                break;
            }
            case '*': {  // Kleene closure
                State *s = stack[stack_top];
                State *new_s = create_state((*state_count)++);
                states[new_s->state_id] = new_s;
                add_transition(new_s, '\0', s->state_id);
                add_transition(s, '\0', new_s->state_id);
                stack[stack_top] = new_s;
                break;
            }
            default: {  // Character
                State *new_state = create_state((*state_count)++);
                states[new_state->state_id] = new_state;
                add_transition(start_state, re[i], new_state->state_id);
                start_state = new_state;
                stack[++stack_top] = start_state;
                break;
            }
        }
    }

    add_transition(start_state, '\0', end_state->state_id);  // Epsilon transition to end state
    return end_state;
}

// Function to print the NFA states and transitions
void print_nfa(State *states[], int num_states) {
    printf("NFA States and Transitions:\n");
    for (int i = 0; i < num_states; i++) {
        State *s = states[i];
        if (s->num_transitions > 0) {
            printf("State %d:\n", s->state_id);
            for (int j = 0; j < s->num_transitions; j++) {
                if (s->symbols[j] == '\0') {
                    printf("  Epsilon --> State %d\n", s->next_states[j]);
                } else {
                    printf("  '%c' --> State %d\n", s->symbols[j], s->next_states[j]);
                }
            }
        }
    }
}

int main() {
    char re[100];  // Input regular expression
    printf("Enter the regular expression: ");
    scanf("%s", re);  // User enters the regular expression

    State *states[MAX_STATES];  // Array to store all states
    int state_count = 0;

    // Convert regular expression to NFA
    State *nfa = re_to_nfa(re, states, &state_count);

    // Print the NFA states and transitions
    print_nfa(states, state_count);

    return 0;
}
