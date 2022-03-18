#include "3140_concur.h"
#include <stdlib.h>
#include <MKL46Z4.h>


void add_process_state(void (*f)(void), int);
void remove_first();
void front_to_back();

process_t *head = NULL;
process_t *tail = NULL;
process_t *current_process = NULL;

struct process_state {
	unsigned int* osp;
	unsigned int* sp;
	int n;
	struct process_state* next;
};

/*
 * creates a process. Interrupts must be disabled
 */


void add_process_state(void (*f)(void), int n) {

	//initializing the linked list if it is null
	struct process_state *elem;

	//allocating memory for the element, assigning its values
	elem = (process_t *) malloc(20);
	elem->n = n;
	elem->sp = process_stack_init(f, n);
	elem->osp = elem->sp;
	elem->next = NULL;

	//if this is the first element to be created
	if (head == NULL) {
		head = elem;
		tail = elem->next;
	}
	else {
		/*
		struct process_state *tmp;
		tmp = head;
		while (tmp->next != NULL) {
			// while there are more elements in the list
			tmp = tmp->next;
		}
		// now tmp is the last element in the list
		 * */

		//if only the head exists
		if(tail == NULL) {
			tail = elem;
			head->next = elem;
		}
		else {
			//set the tail's next to the new element, replace the tail
			tail->next = elem;
			tail = elem;
		}
	}

	return;
}

/*
 * Removes the process at the head, interrupts must be disabled
 */

void remove_first() {
	//if there are any nodes
	if(head != NULL) {
		//if there is only the head node
		if(tail == NULL) {
			//free the head's stack
			process_stack_free(head->osp, head->n);
			//free the head node
			free(head);
			//set head to null
			head = NULL;
		}
		//if at least two nodes exist (head and tail)
		else {
			//remove head, make next element the new head
			struct process_state *tmp;
			tmp = head->next;
			//free the head's stack
			process_stack_free(head->osp, head->n);
			//free the head node
			free(head);
			//set the head to the next process in the LL
			head = tmp;

			//if head and tail point to the same node, make tail NULL
			if(head == tail) {
				tail = NULL;
			}
		}
	}
}

/*
 * Implements RR behavior that moves an interrupted process to the back of the list
 */
void front_to_back() {
	//only proceed if there are atleast two nodes, otherwise do nothing
	if(head != NULL && tail != NULL) {
		//if the head and tail are the only existing nodes
		if(tail == head->next && tail->next == NULL) {
			process_t *tmp = head;
			tail->next = head;
			//put the current tail node into head
			head = tail;
			//store the old head into the tail
			tail = tmp;
			tail->next = NULL;
		}
	}
	//3 or more nodes
	else {
		//set the next node of the tail to the current head node
		tail->next = head;
		//make the old head node the new tail node, and make the next null
		tail = head;
		tail->next = NULL;
		//make the new head node the next element of the old head node
		head = head->next;
	}
}

unsigned int * process_select(unsigned int * cursp) {

}

void process_start() {
	NVIC_EnableIRQ(PIT_IRQn);
	//work on this
	process_begin();
}




