/*
sudo apt install libtevent-dev libtalloc-dev
gcc simple.c -o simple -ltevent -ltacllo 
*/

#include <stdio.h>
#include <unistd.h>
#include <tevent.h>

struct data {
    int x;
};

static void foo_done(struct tevent_req *req) {
    struct data *a = tevent_req_data(req, struct data);
    struct data *b = tevent_req_callback_data(req, struct data);
    struct data *c = (struct data *)tevent_req_callback_data_void(req);
    
    printf("a             @ %p\n", a); // req_data
    printf("b             @ %p\n", b); // callback_data
    printf("c             @ %p\n", c); // callback_data
}

struct tevent_req * foo_send(TALLOC_CTX *mem_ctx, struct tevent_context *event_ctx) {
    struct tevent_req *req;
    struct data *req_data;
    
    req = tevent_req_create(event_ctx, &req_data, struct data);
    printf("req_data      @ %p\n", req_data);
    return req;
}

static void run(struct tevent_context *ev, struct tevent_timer *te, struct timeval current_time, void *private_data) {
    printf("private_data  @ %p\n", private_data); // data

    struct tevent_req *req;
    struct data *callback_data = talloc(ev, struct data);
    printf("callback_data @ %p\n", callback_data);

    req = foo_send(ev, ev);
    tevent_req_set_callback(req, foo_done, callback_data);
    tevent_req_done(req); // call callback(foo_done)
}

int main () {
    struct tevent_context *event_ctx;
    struct data *data;
    TALLOC_CTX *mem_ctx;
    struct tevent_timer *time_event;

    mem_ctx = talloc_new(NULL);
    if (mem_ctx == NULL)
        return EXIT_FAILURE;

    event_ctx = tevent_context_init(mem_ctx);
    if (event_ctx == NULL)
        return EXIT_FAILURE;

    data = talloc(mem_ctx, struct data);
    printf("data          @ %p\n", data);

    time_event = tevent_add_timer(event_ctx, mem_ctx, tevent_timeval_current(), run, data); // create timerevent: call run at tevent_timval_current() which is now 
    if (time_event == NULL)
        return EXIT_FAILURE;

    tevent_loop_once(event_ctx); // trigger timmer event
    tevent_loop_wait(event_ctx); // wait until there are no events in event_ctx (optional)
    talloc_free(mem_ctx);

    return EXIT_SUCCESS;
}
