#' DX_runif
#'
#' @param n 
#' @param k 
#' @param s 
#' @param t 
#'
#' @return
#' @export
#'
#' @examples
dx_runif <- function(n, k=47, s=1, t=1){
  seed <- sample.int(.Machine$integer.max, 1)
  .Call(`_DX_generator_rand_test`, n, seed, k)
}
