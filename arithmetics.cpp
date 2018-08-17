#include <bits/stdc++.h>

using namespace std;
void reverse(int arr[],int m){
    int mid =(m-1)/2;
    for(int i=0;i<=mid;i++){
        int temp=arr[m-i-1];
        arr[m-i-1]=arr[i];
        arr[i]=temp;
    }
}
void pad(int iarr1[],int iarr2[],int m,int n){
    
    if(m>n){
		for(int i=n-1;i>=0;i--){
				iarr2[m-n+i]=iarr2[i];
		}
		for(int i=0;i<m-n;i++){
				iarr2[i]=0;
		}
// 		for(int i=0;i<m;i++){
// 		    cout<<iarr2[i];
// 		}
	}
	else if(n>m){
		for(int i=m-1;i>=0;i--){
			iarr1[n-m+i]=iarr1[i];
		}
		for(int i=0;i<n-m;i++){
			iarr1[i]=0;
		}
// 		for(int i=0;i<n;i++){
// 		    cout<<iarr1[i];
// 		}
    }
    else if(m==n){
        return;
    }

}
int compare(int sarr[],int arr[],int l1,int l2){
    int c;
    if(l2>l1){
        c=0;
        return c;
    }
	pad(sarr,arr,l1,l2);
	int j=0;
	if(sarr[0]>arr[0]){
	    c=1;
	    return c;
	}
	while(sarr[j]==arr[j]&&j<l1){
		j++;
		if(sarr[j]>arr[j]){
			c=1;
			return c;
		}
		else if(sarr[j]<arr[j]){
			c=0;
			return c;
		}
		else if(sarr[j]==arr[j]){
		    j++;
		    if(j==l1){
		        c=1;
		        return c;
		    }
		}
	}
}

int *add(int iarr1[],int iarr2[],int maximum,int m,int n){
	int *oarr = new int[maximum+2];
	oarr[maximum+1]=-1;
	if(m==n){
		    
		    reverse(iarr1,maximum);
	        reverse(iarr2,maximum);
		}
    else{
		    pad(iarr1,iarr2,m,n);
		    reverse(iarr1,maximum);
	        reverse(iarr2,maximum);
		}
	int i;
	int carry=0;
	for(i=0;i<maximum;i++){
		int sum=iarr1[i]+iarr2[i];
		if(carry==1){
			++sum;
		}
		if(sum>9){
			oarr[i]=sum%10;
			carry=1;
		}
		else{
			oarr[i]=sum;
			carry=0;
		}
	}
	if(carry==1){
		oarr[i]=carry;
	}
	else{
		oarr[i]= 0;
	}
	reverse(oarr,(maximum+1));
	if(oarr[0]==0){
	    for(int i=0;i<maximum+1;i++){
	        oarr[i]=oarr[i+1];
	    }
	}
	return oarr;
}

int *subtract(int iarr1[],int iarr2[],int maximum,int m,int n){
    int *oarr = new int[maximum+1];
    oarr[maximum]=-1;
    if(m==n){
		    
		    reverse(iarr1,maximum);
	        reverse(iarr2,maximum);
		}
    else{
		    pad(iarr1,iarr2,m,n);
		    reverse(iarr1,maximum);
	        reverse(iarr2,maximum);
		}
    for(int i=0;i<maximum;i++){
        int diff = iarr1[i]-iarr2[i];
        if(diff<0){
            oarr[i]=diff+10;
            int j=i+1;
            if(iarr1[j]==0){
            	int flag=0;
            while(iarr1[j]==0){
              iarr1[j]=9;
              flag=1;
              j++;
            }
            if(flag){
               iarr1[j]-=1; 
               }
            }
           else{
           	iarr1[j]-=1;
           } 
               
        }
        else{
           oarr[i]=diff; 
        }
    }
    reverse(oarr,maximum);
    int i=0;
    int flag=0;
    int shift=0;
    while(i<maximum){
        if(flag==0&&oarr[i]==0){
        	shift=1;
            i++;
        }
        else{
            flag=1;
            break;
        }
    }
    if(shift){
    	for(int j=0;j<maximum-i+1;j++){
    		oarr[j]=oarr[i+j];
    	}
    }
    return oarr;
}

int *multiply(int iarr1[],int iarr2[],int m,int n,int maximum){
    int *oarr = new int[m+n+1];
    oarr[m+n]=-1;
    for(int i=0;i<m+n;i++){
       oarr[i]=0; 
    }
    if(m==n){
		    
		    reverse(iarr1,maximum);
	        reverse(iarr2,maximum);
		}
    else{
		    pad(iarr1,iarr2,m,n);
		    reverse(iarr1,maximum);
	        reverse(iarr2,maximum);
		}
    int cnt=0;
    int j;
    int carry;
    for(int i=0;i<n;i++){
        carry=0;
        for(j=0;j<m;j++){
            int product = iarr1[j]*iarr2[i];
            if(carry){
                product+=carry;
            }
            oarr[j+cnt]+=product;
            if(oarr[j+cnt]>9){
                carry=oarr[j+cnt]/10;
                oarr[j+cnt]=oarr[j+cnt]%10;
            }
        }
        if(carry){
            oarr[j+cnt]=carry;
        }
        cnt++;
    }
    reverse(oarr,(m+n));
    if(oarr[0]==0){
	    for(int i=0;i<m+n;i++){
	        oarr[i]=oarr[i+1];
	    }
	}
	return oarr;
}
int *subtract2(int sarr[],int arr[],int l1,int l2){
	int maximum=max(l1,l2);
	if(l1==l2){
		    
		    reverse(sarr,maximum);
	        reverse(arr,maximum);
		}
	else{
	    pad(sarr,arr,l1,l2);
		reverse(sarr,maximum);
	    reverse(arr,maximum);
	}
	int *oarr = new int[maximum+1];
    oarr[maximum]=-1;
    for(int i=0;i<maximum;i++){
        int diff = sarr[i]-arr[i];
        if(diff<0){
            oarr[i]=diff+10;
            int j=i+1;
            if(sarr[j]==0){
            	int flag=0;
            while(sarr[j]==0){
              sarr[j]=9;
              flag=1;
              j++;
            }
            if(flag){
               sarr[j]-=1; 
               }
            }
           else{
           	sarr[j]-=1;
           } 
               
        }
        else{
           oarr[i]=diff; 
        }
    }
    reverse(oarr,maximum);
    return oarr;	
}
int *multiply2(int iarr2[],int table,int n){
    int *oarr = new int[n+2];
    oarr[n+1]=-1;
    reverse(iarr2,n);
    for(int i=0;i<n+1;i++){
       oarr[i]=0; 
    }
    int j;
    int carry=0;
    for(j=0;j<n;j++){
        int product = iarr2[j]*table;
        if(carry){
            product+=carry;
        }
        oarr[j]=product;
        if(oarr[j]>9){
            carry=oarr[j]/10;
            oarr[j]=oarr[j]%10;
        }
    }
    if(carry){
        oarr[j]=carry;
    }
    reverse(oarr,n+1);
    if(oarr[0]==0){
	    for(int i=0;i<n+1;i++){
	        oarr[i]=oarr[i+1];
	    }
	}
    return oarr;
}
int *divide(int iarr1[],int iarr2[],int m,int n){
	int sarr[m];
	int c=compare(iarr1,iarr2,n,n);//returns 1 when iarr1>iarr2 for n digits
	int arrlen;
	if(c==1)arrlen=n;
	else arrlen=n+1;
	int *div = new int[m-arrlen+1];
	for(int i=0;i<arrlen;i++){
		sarr[i]=iarr1[i];
	}
	int k;
	for(k=0;k<m-arrlen+1;k++){
		int arr[n+1];
		int j;
		int i;
		int c1;
		for(i=9;i>0;i--)
			j=0;
			int table=i;
			int *p=multiply2(iarr2,table,n);
			int c2;
			// if(*(p+arrlen)!=-1){
			// 	break;
			// }
			while(*(p+j)!=-1){
				arr[j]=*(p+j);
				j++;
			}
			c2=compare(sarr,arr,arrlen+k,j);
			if(c2==1){
				break;
			}
		}
		div[k]=i;
		int *p=subtract2(sarr,arr,arrlen+k,j);
	 	int t=0;
		while(*(p+t)!=-1){
			sarr[t]=*(p+t);
			t++;
		}
		if(t>m-1){
			break;
		}
		sarr[t]=iarr1[arrlen+k];
		c1=compare(sarr,iarr2,arrlen+k+1,n);
		int flag=0;
		if(c1==1){
			continue;
		}
		else{
			while(c1!=1){
				t++;
				k++;
				if(k=m-arrlen+1){
					flag=1;
					break;
				}
				div[k]=0;
				sarr[t]=iarr1[arrlen+k];
				c1 = compare(sarr,iarr2,arrlen+k+1,n);
			}
		}
		if(flag)break;
		if(c1){
			continue;
		}
	}
	div[k]=-1;
	return div;
}


int main(){
	int T;
	cin>>T;
//	cout<<"\n";
	for(int i=0;i<T;i++){
		int m,n;
		int op;
		cin>>m>>n;
		int maximum = max(m,n);
		char icarr1[maximum];
		char icarr2[maximum];
		int iarr1[maximum];
		int iarr2[maximum];
		for(int i=0;i<m;i++){
			cin>>icarr1[i];
			icarr1[i]-=48;
			iarr1[i]=icarr1[i];
		}
		for(int i=0;i<n;i++){
			cin>>icarr2[i];
			icarr2[i]-=48;
			iarr2[i]=icarr2[i];
		}
		
		cin>>op;
	    if(op==1){
	    	int *p;
	    	p=add(iarr1,iarr2,maximum,m,n);
	    	int i=0;
	    	while(*(p+i)!=-1){
	    		cout<<*(p+i);
	    		i++;
	    	}
	    }
	     if(op==2){
	       int *p;
	    	p=subtract(iarr1,iarr2,maximum,m,n);
	    	int i=0;
	    	while(*(p+i)!=-1){
	    		cout<<*(p+i);
	            i++;
	    	}
        }
        if(op==3){
            int *p;
            p=multiply(iarr1,iarr2,m,n,maximum);
            int i=0;
            while(*(p+i)!=-1){
                cout<<*(p+i);
                i++;
            }
        }
        if(op==4){
    	    if(strcmp(icarr1,icarr2)<0){
    		    cout<<0;
    	    }
    	    else{
    		    int *p;
	            p=divide(iarr1,iarr2,m,n);
	            int i=0;
	            while(*(p+i)!=-1){
	                cout<<*(p+i);
	                i++;
	            }
    	    }
        }
        cout<<"\n";
   }
  return 0;
}
