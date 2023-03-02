#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "queue.h"

#define MAXV 100 
 
typedef enum {FALSE,TRUE} bool;

bool visited[6];
typedef struct edgenode{
    int y;
    int weight;
    struct edgenode *next;
} edgenodeT;

typedef struct {
    edgenodeT *edges[MAXV +1];
    int degree[MAXV+1];
    int nvertices;
    int nedges;
    bool directed;
} graphT;

void initialize_graph(graphT *g, bool directed);
void read_graph(graphT *g,char *filename);
void insert_edge(graphT *g, int x,int y,int w);
void print_graph(graphT *g,char *name);
void free_graph(graphT *g);
void delete_edge(graphT *g, int from , int to);
void print_degree(graphT *g);
void print_complement(graphT *g ,int k);
void eliminatelinks(graphT *g, int minW, int maxW);
void differentlinks(graphT *g , graphT *c);
void commonlinks(graphT *g , graphT *c);
void dfs(graphT *myg1, int k);
void bfs(graphT *g, int k);
bool is_connected(graphT *g);
void num_of_conn_comp(graphT *g);
graphT *copy_graph(graphT *g);
void print_options();

int main(int argc, char *argv[]){
    graphT *myg1=NULL , *myg2 = NULL;
    const char space[2] = " ";
    char *v, *d, *i, *quit = "quit\n";
    char input[40];
    
     if(argc <2 ){
         fprintf(stderr,"Usage: %s graph_name" , argv[0]);
         exit(-1);
     }
    myg1 = (graphT *)malloc(sizeof(graphT));
    if(myg1==NULL){
        fprintf(stderr,"Cannot allocate memory for the graph");
        exit(-1);
    }
    
    initialize_graph(myg1, FALSE);
    read_graph(myg1, argv[1]);
    print_graph(myg1, "myg1");    
    myg2 = copy_graph(myg1);
    print_graph(myg2,"myg2");
  
    while(TRUE){
    print_options();
    fgets(input,40,stdin);

    v = strtok(input ,space);
    d = v + strlen(v) + 1;
     
    if(strcmp(v, "insert")==0){ //Insert Section
        int l,j,k;
        
        i = strtok(d ,space);
        l =atoi(strtok(NULL ,space));
        j =atoi(strtok(NULL ,space));
        k =atoi(strtok(NULL ,space));
        if(strcmp(i,"myg1")==0){
            
            insert_edge(myg1,l,j,k);
            if(myg1->directed ==FALSE){
                     insert_edge(myg1,j, l, k);
                }
        }else{

            insert_edge(myg2,l,j,k);
            if(myg2->directed ==FALSE){
                     insert_edge(myg2,j, l, k);
                }
        }     
        
    }else if(strcmp(v, "delete")==0){ // Delete Argument
        int l,j;
        i = strtok(d ,space);
        l =atoi(strtok(NULL ,space));
        j =atoi(strtok(NULL ,space));
        
        if(strcmp(i,"myg1\n")==0){
            
            delete_edge(myg1,l,j);
            delete_edge(myg2,j,l);
            
        }else{
            delete_edge(myg1,l,j);
           delete_edge(myg2,j,l);
        }
        
    }

    else if(strcmp(v, "printgraph")==0){ // Prind Graph Argument

        i = strtok(d ,space);
        if(strcmp(i,"myg1\n")==0){
            
            print_graph(myg1,"myg1");
        }else{
            print_graph(myg2,"myg2");
        }

        
    }

 
    else if(strcmp(v, "printdegree")==0){ // Degree Argument
        i = strtok(d ,space);
        if(strcmp(i,"myg1\n")==0){
            print_degree(myg1);
        }else{
            print_degree(myg2);
        }
    }

    else if(strcmp(v, "printcomplement")==0){ // Print Complement Argument
        int k ;
        k = 0;
        i = strtok(d ,space);
        if(strcmp(i,"myg1\n")==0){
            
            print_complement(myg1,k);
            
        }else{
            
            print_complement(myg2,k);
        }
    }

    else if(strcmp(v, "eliminatelinks")== 0){ // Eliminate Links Argument
        int k;
        int l;
        i = strtok(d ,space);
        k =atoi(strtok(NULL ,space));
        l =atoi(strtok(NULL ,space));
        if(strcmp(i,"myg1")==0){

            
            eliminatelinks(myg1,k,l);
        }else{

            
            eliminatelinks(myg2,k,l);
        }
       
    }

    else if(strcmp(v, "differentlinks")==0){ // Different Links Argument
        char *k;
        i = strtok(d ,space);
        k = strtok(NULL ,space);
        if(strcmp(i,"myg1\n")==0){
            
            differentlinks(myg1,myg2);
        }else{
            
            differentlinks(myg2,myg1);
        }

    }else if(strcmp(v, "commonlinks")==0){ // Comon Links Argument
        char *k;
        i = strtok(d ,space);
        k = strtok(NULL ,space);
        if(strcmp(i,"myg1\n")==0){
            
            commonlinks(myg1,myg2);
        }else{
            
            commonlinks(myg2,myg1);
        }
    }    
    
    else if(strcmp(v, "dfs")==0){ // DFS Argument
        int k;
        i = strtok(d ,space);
        k = atoi(strtok(NULL ,space));
       
        if(strcmp(i,"myg1\n")==0){
            
            int j ;
            for(j=1 ; j<= myg1->nvertices ; j++){
                visited[j] = FALSE;
            }
            dfs(myg1,k);
        }else{
            
            int j ;
            for(j=1 ; j<= myg2->nvertices ; j++){
                visited[j] = FALSE;
            }
            dfs(myg2,k);
        }
    }
     
  else if(strcmp(v, "bfs")==0){  // BFS Argument
        char *i;
        int k;
        i = strtok(d ,space);
        k = atoi(strtok(NULL ,space));
        
        if(strcmp(i,"myg1\n")==0){
              
            bfs(myg1,k);
        }else{
            
            bfs(myg2,k);
        }
    }    
    
    else if(strcmp(v, "isconnected")==0){ // Connected Argument
        
        char *i;
        i = strtok(d ,space);
        if(strcmp(i,"myg1\n")==0){
            
            if(is_connected(myg1)){
                printf("connected");
            }else{
                printf("not - connected");
            }
            
        }else{
            
            if(is_connected(myg2)){
                printf("connected");
            }else{
                printf("not - connected");
            }
        }
    }

    else if(strcmp(v, "numofconncomp")==0){ // Number of Connected Components argument
         
        
        i = strtok(d ,space);
        if(strcmp(i,"myg1\n")==0){
            
            num_of_conn_comp(myg1);
            
        }else{
            
            num_of_conn_comp(myg2);
        }
        
        
    }

    else if(strcmp(v, "quit\n")==0){ // Quit
        exit(0);
    }
    else{
         printf("something wrong with command try again\n");
    }
 }
    free_graph(myg1);
    free_graph(myg2);

}


void initialize_graph(graphT *g,bool directed){
    int i;
    g->nvertices =0;
    g->nedges =0;
    g->directed = directed ;
    for(i=1; i<=MAXV ; i++){
        g->edges[i] = NULL;
    }
    for(i=1; i<=MAXV ; i++){
        g->degree[i] = 0;
    }

}

void read_graph(graphT *g,char *filename){
    int i;
    int n,m, dir;
    int x,y,w;
    FILE *fp;
    if((fp = fopen(filename,"r"))==NULL){
        fprintf(stderr,"Cannot open the graph file");
        exit(-1);
    }
    fscanf(fp,"%d %d %d",&n,&m,&dir);
    g->nvertices = n;
    g->nedges = 0;
    g->directed = dir;
    for(i=1;i<=m;i++){
        fscanf(fp,"%d %d %d",&x , &y , &w);
        insert_edge(g,x,y,w);
        if(dir==FALSE){
            insert_edge(g,y,x,w);
        }
    }
    fclose(fp);
}

void insert_edge(graphT *g,int x,int y,int w){
    edgenodeT *pe;
    pe = malloc(sizeof(edgenodeT));
    if(pe==NULL){
        fprintf(stderr,"Cannot allocate memory for the node" );
        exit(-1);
    }

    pe->weight = w ;
    pe->y = y;
    if(g->edges[x] == NULL){
        pe->next = g->edges[x];
        g->edges[x] = pe;
    }else{
        edgenodeT *checker;
        checker = g->edges[x];
        while(checker != NULL){
            if( checker->y == y){
                return ;
            }
            checker = checker->next;
        }
        edgenodeT *qe;
        qe = g->edges[x];
        
        if(qe->y > pe->y){
           pe->next = qe;
           g->edges[x] = pe;
        }else{
            while((qe->next !=NULL) && ((qe->next->y) < (pe->y))){
                qe = qe->next;
            }
          pe->next = qe->next;
          qe->next = pe;
        }
    }
    g->degree[x]++;
    g->nedges++;
}


void print_graph(graphT *g,char *name){
    edgenodeT *pe;
    int i;
    if(!g) {
        
       return;
    }
    printf("Graph Name: %s\n",name);
    for(i=1;i<=g->nvertices;i++){
        printf("Node %d: ",i);
        pe = g->edges[i];
        while(pe ){
            printf(" %d(w=%d),", pe->y,pe->weight);
            pe = pe->next;
        }
    printf("\n");
    }
}

void free_graph(graphT *g){
    edgenodeT *pe, *olde;
    int i;
    for(i=1;i<=g->nvertices;i++){
        printf("Node %d: ",i);
        pe = g->edges[i];
        while(pe){
            olde = pe;
            pe = pe->next;
            free(olde);
        }
    free(g);
    }
}

void delete_edge(graphT *g, int from , int to){
    edgenodeT *cp, *prev, *tmp;
    
    prev = NULL;
    cp = g->edges[from];
    
    while(cp){
        if(cp == g->edges[from]){
            if(cp->y == to){
                tmp = cp->next;
                free(cp);
                g->edges[from] = tmp;
                cp = tmp;
            }else{
                prev = cp;
                cp = cp->next;
            }
        }else{
            if(cp->y == to){
                prev->next = cp->next;
                free(cp);
                cp = prev->next;
            }else{
                prev = cp;
                cp = cp->next;
            }
        }
    }
}

graphT *copy_graph(graphT *g){
    graphT *newg;
    edgenodeT *gn ; 
    edgenodeT *cn ; 
    int i ;
    newg = (graphT *)malloc(sizeof(graphT));
    initialize_graph(newg, g->directed);
    newg->nedges = g->nedges;
    newg->nvertices = g->nvertices;

    for( i = 1 ; i <= g->nvertices ; i++){
        gn = g->edges[i];
        if(gn == NULL){
            
            newg->edges[i] = NULL;
        }
        else{

            while(gn != NULL){
                insert_edge(newg, i, gn->y,gn->weight);
                if(g->directed ==FALSE){
                     insert_edge(newg,gn->y, i, gn->weight);
                }
                gn = gn->next;
            }
        }
    }
    return newg;
}

void print_degree(graphT *g){
    int i;
    if(g->directed == FALSE){
        //for an directed graph
        for(i=1 ; i<= g->nvertices ; i++){
            printf("number of vertices in node %d is %d\n", i , g->degree[i]);
        }
    }else{
        //for an directed graph
        for(i=1 ; i<= g->nvertices ; i++){
            printf("number of vertices in node %d is %d\n", i , g->degree[i]);
        }
    }

}
void print_complement(graphT *g , int p){ 
     int i , k;   
     graphT *cg ;
     edgenodeT *ge;
     cg = (graphT *)malloc(sizeof(graphT));
     if(cg == NULL){
         fprintf(stderr,"Cannot allocate memory for the graph" );
         exit(-1);
     }
     initialize_graph(cg , g->directed);
    cg->directed = g->directed;
    cg->nedges = g->nedges;
    cg->nvertices = g->nvertices;
    for(i = 1  ; i <= g->nvertices; i++){
        for(k =1 ; k <= g->nvertices; k++){
            insert_edge(cg,i,k,1);
        }
    }
    differentlinks(cg, g);
}

void eliminatelinks(graphT *g, int minW, int maxW){
    edgenodeT *temp , *prev;
    int i;
    for(i = 1; i <= 6 ; i++){
        printf("%d", i);
        temp = g->edges[i];
        while (temp != NULL && (temp->weight < minW || temp->weight > maxW)){
            g->edges[i] = temp->next;
            free(temp); 
            temp = g->edges[i]; 
        }
         
        while(temp != NULL){
            while(temp!= NULL  && (temp->weight >= minW && temp->weight <= maxW)){
                prev = temp;
                temp = temp->next;
            }
            if(  temp == NULL){
                break;
            }
            prev->next = temp->next;
            g->degree[i]--;
            free(temp);
            temp  = prev->next;
        }
    }
}

void differentlinks(graphT *g , graphT *c){
    edgenodeT *gn , *cn;
    int i ;
    for(i = 1  ; i <= g->nvertices; i++){
        gn = g->edges[i];
        cn = c->edges[i];
        printf("Node %d: ",i);
        
        if(gn == NULL){
           
           continue;
        }
        else{
            
            while(gn != NULL){
               bool exist = FALSE;
               while(cn != NULL){
                   if (gn->y == cn->y){
                       exist = TRUE;
                   }
                cn = cn->next;
                
               }
               if (exist == FALSE){
                    printf("%d(w=%d), ", gn->y,gn->weight );       
                }
            cn = c->edges[i];
            gn = gn->next;
            }
        }
            
    printf("\n");
    }
}
void commonlinks(graphT *g , graphT *c){
    
    edgenodeT *gn , *cn;
    int i ;
    for(i = 1  ; i <= g->nvertices; i++){
        gn = g->edges[i];
        cn = c->edges[i];
        printf("Node %d: ",i);
        
        if(gn == NULL){
           
           continue;
        }
        else{
            
            while(gn != NULL){
               bool exist = FALSE;
               while(cn != NULL){
                   if (gn->y == cn->y){
                       exist = TRUE;
                   }
                cn = cn->next;
                
               }
               if (exist){
                    printf("%d(w=%d), ", gn->y,gn->weight );       
                }
            cn = c->edges[i];
            gn = gn->next;
            }
        }      
    printf("\n");
    }
}




void dfs(graphT *g, int k){
    printf("%d->",k);
    
    edgenodeT *pe;
    pe = g->edges[k];
    visited[k]=TRUE;
    while(pe != NULL){
        k = pe->y;
        if(!visited[k]){
            dfs(g,k);
        }
        pe = pe->next;
    }
}

void bfs(graphT *g, int k){

    create();
    edgenodeT *pe;
    pe = g->edges[k];
    int i, bvisited[g->nvertices] ,w ,p;
    for(i= 1;i<=g->nvertices;i++){
        bvisited[i] = 0;
    }
    enq(k);
    bvisited[k] = 1;
    printf("\nVisited\t%d",k);

    while(queuesize() != 0){
    
        p = deq();
        pe = g->edges[p];
        while(pe != NULL){
         
            w = pe->y;
         
            if(bvisited[w]==0){
            enq(w);
            bvisited[w]=1;
            printf("-> %d",w);
            }
            pe = pe->next;
        }
    }
}

bool is_connected(graphT *g){
    if(g->directed== TRUE){
        printf("Purchase the next version of this program :)");
        return FALSE;
    } else{
        
        bool connected ;
        connected = TRUE;

        create();
        edgenodeT *pe;
        pe = g->edges[1];
        int i, bvisited[g->nvertices] ,w ,p;
        for(i= 1;i<=g->nvertices;i++){
            bvisited[i] = 0;
        }
        enq(1);
        bvisited[1] = 1;

        while(queuesize() != 0){
    
            p = deq();
            pe = g->edges[p];
            while(pe != NULL){
         
                w = pe->y;
                if(bvisited[w]==0){
                    enq(w);
                    bvisited[w]=1;
                }
                pe = pe->next;
            }
        }
        for(i= 1;i<=g->nvertices;i++){
            if(bvisited[i] == 0){
                connected =FALSE;
            }
        }
        
        return connected;
    }

}
void num_of_conn_comp(graphT *g){
    if(g->directed== TRUE){
        printf("Purchase the next version of this program :)");
    } else{
        if(is_connected(g)){
            printf("%d number of connected components.", g->nvertices);
        }
        
    }

}

void print_options(){
    printf("\n-----------------------------------------------------------------------------\n");
    printf("* insert                    [myg1 | myg2] x y w\n");
    printf("* delete                    [myg1 | myg2] x y\n\n");
    printf("* printgraph                [myg1 | myg2]\n");
    printf("* printdegree               [myg1 | myg2]\n");
    printf("* printcomplement           [myg1 | myg2]\n\n");
    printf("* eliminatelinks            [myg1 | myg2] minW maxW\n");
    printf("* differentlinks            [myg1 | myg2] [myg1 | myg2]\n");
    printf("* commonlinks               [myg1 | myg2] [myg1 | myg2]\n\n");
    printf("* dfs                       [myg1 | myg2] x\n");
    printf("* bfs                       [myg1 | myg2] x\n");
    printf("* isconnected               [myg1 | myg2]\n");
    printf("* numofconncomp             [myg1 | myg2]\n\n");
    printf("* quit\n");
    printf("-----------------------------------------------------------------------------\n\n");
}