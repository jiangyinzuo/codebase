//! https://leetcode-cn.com/problems/lru-cache-lcci/

use std::collections::HashMap;
use std::ptr::NonNull;

struct LRUNode {
    key: i32,
    value: i32,
    next: *mut LRUNode,
    prev: *mut LRUNode,
}

impl LRUNode {
    fn new_empty() -> Self {
        LRUNode {
            key: 0,
            value: 0,
            next: std::ptr::null_mut(),
            prev: std::ptr::null_mut(),
        }
    }

    fn new(key: i32, value: i32) -> Self {
        LRUNode {
            key,
            value,
            next: std::ptr::null_mut(),
            prev: std::ptr::null_mut(),
        }
    }
}

fn detach(n: *mut LRUNode) {
    debug_assert!(!n.is_null());
    unsafe {
        debug_assert!(!(*n).next.is_null());
        debug_assert!(!(*n).prev.is_null());
        (*(*n).next).prev = (*n).prev;
        (*(*n).prev).next = (*n).next;
    }
}

struct LRUCache {
    hash_map: HashMap<i32, Box<LRUNode>>,
    head: LRUNode,
    tail: LRUNode,
    cap: i32,
}

/**
 * `&self` means the method takes an immutable reference.
 * If you need a mutable reference, change it to `&mut self` instead.
 */
impl LRUCache {
    fn new(capacity: i32) -> Self {
        let mut cache = LRUCache {
            hash_map: HashMap::with_capacity(capacity as usize),
            head: LRUNode::new_empty(),
            tail: LRUNode::new_empty(),
            cap: capacity,
        };
        cache.head.next = &mut cache.tail;
        cache.tail.prev = &mut cache.head;
        cache
    }

    fn get(&mut self, key: i32) -> i32 {
        match self.hash_map.get_mut(&key) {
            Some(v) => {
                let value = v.value;
                detach(v.as_mut());
                let v = v.as_mut() as *mut _;
                self.attach_to_head(v);
                value
            }
            None => -1,
        }
    }

    fn put(&mut self, key: i32, value: i32) {
        match self.hash_map.get_mut(&key) {
            Some(v) => {
                v.value = value;
                let v = v.as_mut() as *mut _;
                detach(v);
                self.attach_to_head(v);
            }
            None => {
                let mut n = Box::new(LRUNode::new(key, value));
                self.attach_to_head(n.as_mut());
                self.hash_map.insert(key, n);
                if (self.cap as usize) < self.hash_map.len() {
                    debug_assert!(!self.tail.prev.is_null());
                    self.hash_map.remove(unsafe { &(*(self.tail).prev).key });
                    detach(self.tail.prev);
                }
            }
        }
    }

    fn attach_to_head(&mut self, n: *mut LRUNode) {
        unsafe {
            debug_assert!(!self.head.next.is_null());
            (*n).next = self.head.next;
            (*n).prev = &mut self.head;
            self.head.next = n;
            (*(*n).next).prev = n;
        }
    }
}

/**
 * Your LRUCache object will be instantiated and called as such:
 * let obj = LRUCache::new(capacity);
 * let ret_1: i32 = obj.get(key);
 * obj.put(key, value);
 */
struct Foo;

#[test]
fn test() {
    let mut cache = LRUCache::new(2 /* 缓存容量 */);

    cache.put(1, 1);
    cache.put(2, 2);
    println!("{}", cache.get(1)); // 返回  1
    cache.put(3, 3); // 该操作会使得密钥 2 作废
    println!("{}", cache.get(2)); // 返回 -1 (未找到)
    cache.put(4, 4); // 该操作会使得密钥 1 作废
    println!("{}", cache.get(1)); // 返回 -1 (未找到)
    println!("{}", cache.get(3)); // 返回  3
    println!("{}", cache.get(4)); // 返回  4
}
