#include <linux/init.h>
#include <linux/module.h>
#include <linux/netfilter.h>
#include <linux/socket.h>/*PF_INET*/
#include <linux/netfilter_ipv4.h>/*NF_IP_PRE_FIRST*/
#include <linux/skbuff.h>
#include <linux/netdevice.h>
#include <linux/inet.h> /*in_aton()*/
#include <net/ip.h>
#include <net/tcp.h>
#define ETHALEN 14
MODULE_LICENSE("GPL");
MODULE_AUTHOR("bbo");
struct nf_hook_ops nfho; 
unsigned int checksum(unsigned int hooknum,
                        struct sk_buff *__skb,
                        const struct net_device *in,
                        const struct net_device *out,
                        int (*okfn)(struct sk_buff *))
{
    struct sk_buff *skb;
    struct net_device *dev;
    struct iphdr *iph;
    struct tcphdr *tcph;
    int tot_len;
    int iph_len;
    int tcph_len;
    int ret;
    skb = __skb;
    if(skb == NULL)
        return NF_ACCEPT;
    iph = ip_hdr(skb);
    if(iph == NULL)
        return NF_ACCEPT;
    tot_len = ntohs(iph->tot_len);
    if(iph->daddr == in_aton("173.26.100.224"))
    {
        iph_len = ip_hdrlen(skb);/*in ip.h*/
        skb_pull(skb,iph_len);//skb->data指针定位到了传输层
        skb_reset_transport_header(skb);/*重置首部长度,现在的首部长度包括了的ip首部长度*/
        if(iph->protocol == IPPROTO_TCP)
        {
            tcph = tcp_hdr(skb);
            tcph_len = tcp_hdrlen(skb);
            if(tcph->dest == htons(3306)) //根据自己得需求来进行过滤数据包
            {
                iph->saddr = in_aton("1.2.3.4");
                dev = dev_get_by_name(&init_net,"eth0");
                tcph->check = 0;
                skb->csum = csum_partial((unsigned char *)tcph, tot_len - iph_len,0);
                tcph->check = csum_tcpudp_magic(iph->saddr,
                        iph->daddr,
                        ntohs(iph->tot_len) - iph_len,iph->protocol,
                        skb->csum);
                iph->check = 0;
                iph->check = ip_fast_csum(iph,iph->ihl);
    
                skb->ip_summed = CHECKSUM_NONE;
                skb->pkt_type = PACKET_OTHERHOST;
                skb->dev = dev;
                skb_push(skb,iph_len);/*在返回之前，先将skb中得信息恢复至原始L3层状态*/
                //skb_reset_transport_header(skb);
                skb_push(skb, ETHALEN);//将skb->data指向l2层，之后将数据包通过dev_queue_xmit()发出
                ret = dev_queue_xmit(skb);
                if(ret < 0)
                {
                    printk("dev_queue_xmit() error\n");
                    goto out;
                }
                return NF_STOLEN;
            }
     }
        skb_push(skb,iph_len);/*在返回之前，先将skb中得信息恢复至原始L3层状态*/
        skb_reset_transport_header(skb);
    }
    
    return NF_ACCEPT;
out:
    dev_put(dev);
    //free(skb);
    return NF_DROP;
}
static int __init filter_init(void)
{
    int ret;
        nfho.hook = checksum;
        nfho.pf = AF_INET;
        nfho.hooknum = NF_INET_PRE_ROUTING;
        nfho.priority = NF_IP_PRI_FIRST;
    
        ret = nf_register_hook(&nfho);
        if(ret < 0)
        {
            printk("%s\n", "can't modify skb hook!");
            return ret;
        }
    return 0;
}
static void filter_fini(void)
{
    nf_unregister_hook(&nfho);
}
module_init(filter_init);
module_exit(filter_fini);