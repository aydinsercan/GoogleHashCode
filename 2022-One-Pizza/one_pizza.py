import os

def score(ingredients, likes, dislikes):
    ret = 0
    for like, dislike in zip(likes, dislikes):
        like = like.split()[1:]
        
        fail = False
        for ing in like:
            if ing not in ingredients:
                fail = True
                break
        
        if not fail:
            dislike = dislike.split()[1:]
            for ing in dislike:
                if ing in ingredients:
                    fail = True
                    break
        if not fail:
            ret += 1

    return ret


with open("c.txt","r") as f:
    in_lines = f.read().splitlines()

C = int(in_lines[0])

likes = in_lines[1:][::2]
dislikes = in_lines[1:][1::2]

like_dic = dict()
dislike_dic = dict()

for like in likes:
    like = like.split()
    for i in like[1:]:
        if i in like_dic:
            like_dic[i] += 1
        else:
            like_dic[i] = 1



for dislike in dislikes:
    dislike = dislike.split()
    for i in dislike[1:]:
        if i in dislike_dic:
            dislike_dic[i] += 1
        else:
            dislike_dic[i] = 1
            
diff_dic = dict()
for key, val in dislike_dic.items():
    if key in like_dic:
        diff_dic[key] = like_dic[key] - val
    else:
        diff_dic[key] = 0 - val

print(diff_dic)
            
sorted_likes = sorted(like_dic.items(), reverse=True)
sorted_dislikes = sorted(dislike_dic.items(), reverse=True)
sorted_diff = sorted(diff_dic.items())

selected_ingredients = [ i[0] for i in sorted_likes]
all_ing = [ i[0] for i in sorted_likes]

for name, count in sorted_diff:
    if count < 0:
        if name in selected_ingredients:
            selected_ingredients.remove(name)
    else:
        break

print(selected_ingredients)
print(all_ing)

for k in range(1):
    max_score = 0
    for i in all_ing:
        tmp = selected_ingredients.copy()
        if i in tmp:
            tmp.remove(i)
        else:
            tmp.append(i)
        tmp_score = score(tmp, likes, dislikes)
        if tmp_score > max_score:
            max_score = tmp_score
            selected_ingredients = tmp.copy()

with open("c_out.txt", 'w') as f:
    f.write(f'{len(selected_ingredients)}')
    for ing in selected_ingredients:
        f.write(f' {ing}')
